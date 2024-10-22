#include "delay.h"

#define TRIGGER (1<<2)
#define ECHO ((IOPIN0>>3)&1)


void Ultrasonic_init(void);
void send_pulse(void);
unsigned int get_range(void);
void timer1delay(unsigned int );

void Ultrasonic_init(void){
	IODIR |= TRIGGER;
	T1TCR = 0;
	T1PR = 59;
}

void send_pulse()
{
    T1TC=T1PC=0;
    IOSET0=TRIGGER;                            
    T1delay(10);                        
    IOCLR0=TRIGGER;                           
}

unsigned int get_range()
{
    unsigned int get=0;
    send_pulse();
    while(!ECHO);
    T0TCR=0x01;
    while(ECHO);
    T0TCR=0;
    get=T1TC;
    if(get<38000)
        get=get/59;
    else
        get=0;
    return get;
}

void T1delay(unsigned int b)  
{
    T1CTCR=0X0000;
    T1PR=59;
    T1MR0=b;
    T1MCR=0x00000004;
    T1TCR=0X02;
    T1TCR=0X01;
    while(T1TC!=T1MR0);
    T1TC=0;
}