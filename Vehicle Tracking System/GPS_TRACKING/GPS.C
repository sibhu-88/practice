#include <stdio.h>
#include <string.h>
#include "delay.h"

#define LCD_DATA1 24
#define RS1 23
#define RW1 22
#define EN1 21

/*----- GPS Functions -----*/
void UART1_ISR(void) __irq;
void GSM_SMS(void);
void GPS(void);
void GPS_CONFIG(void);
void UART_INTERRUPT(void);

char namegps[13], name1gps[13] = "CGPSINFO: 1,", gpsdat[63], Ndat[13], Edat[13];
char msggps, checkgps;
int h, n = 0, k = 0;
unsigned char f;

void GPS(void)
{
  UART_INTERRUPT();
  GPS_CONFIG();
  GSM_SMS();
}

void UART_ISR(void) __irq
{

  if ((U0LSR & 1) != 0)
  {
    msggps = U0RBR;

    if (msggps == '+')
    {
      U0IER = 0X00;

      for (f = 0; f <= 13; f++)
      {
        while (!(U0LSR & 0x01))
          ;
        namegps[f] = U0RBR;
      }
      checkgps = strcmp(namegps, name1gps);
      if (checkgps == 0)
      {
        for (f = 0; f <= 16; f++)
        {
          while (!(U0LSR & 0x01))
            ;
          gpsdat[f] = U0RBR;
        }
        gpsdat[f] = '\0';

        /*----- GPS North Location -----*/
        /*
        for (h = 2; h < 9; h++)
        {
          Ndat[n++] = gpsdat[h];
        }
        strncat(Ndat, " N", 3);
        */

        /*----- GPS East Location -----*/
        /*
        for (h = 10; h < 18; h++)
        {
          Edat[k++] = gpsdat[h];
        }
        strncat(Edat, " E", 3);
        */
      }
      U0IER = 0x01;
    }
  }

  VICVectAddr = 0x00000000;
}

void UART_INTERRUPT(void)
{

  VICIntSelect = 0;
  VICVectCntl0 = 1 << 5 | 6;
  VICVectAddr0 = (unsigned)UART_ISR;
  VICIntEnable = 0x0040;
  U0IER = 0x01;
}

void GPS_CONFIG(void)
{
  delay_milisec(1000);

  UART_STR_TX("AT\r\n");
  delay_milisec(1000);

  UART_STR_TX("AT+CGPS=1\r\n");
  delay_milisec(1000);

  UART_STR_TX("AT+CGPSINFO");
  delay_milisec(1000);
}

// Function to send SMS using GSM module
void GSM_SMS(void)
{
  delay_milisec(1000);

  UART_STR_TX("AT\r\n");
  delay_milisec(1000);

  UART_STR_TX("AT+CMGF=1\r\n");
  delay_milisec(1000);

  UART_STR_TX("AT+CMGS=\"0123456789\"\r\n");
  delay_milisec(1000);

  UART_STR_TX("your car location :");
  UART_STR_TX(gpsdat);
  UART_TX(0x1A);
}
