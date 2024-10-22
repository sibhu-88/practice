#include <lpc21xx.h>
#include "A:\project\Vehicle Tracking System\header\lcd.h"
// #include "A:\project\Vehicle Tracking System\header\ADC.h"
#include "A:\project\Vehicle Tracking System\header\delay.h"
#include "A:\project\Vehicle Tracking System\header\pwm.h"
#include "A:\project\Vehicle Tracking System\header\typedef.h"

unsigned int speed=0,i;

int main(){
	LCD_INIT();
	//ADC_INIT();
	PWM_INT();
	LCD_STR("Speed : ");
	
 	while(1) {
        speed= 50;
// 		((ADC_Read() / 1023) * 100); 		
		// LCD_INT(speed);
//         LCD_STR(" km/h");
 		PWM(speed);
//         delay_milisec(50);
    }
}


