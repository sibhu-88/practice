#include <lpc21xx.h>
#include "A:\project\Vehicle Tracking System\header\uart.h"
#include "gps.c"


#define SW ((IOPIN0 >> 14) & 1)

int main()
{

	UART_INIT();
	while (1)
	{
		if (SW==0)
		{
			GPS();
			delay_milisec(150);
		}
	}
	
}
