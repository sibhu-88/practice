void PWM_INT(void);
void pwm_read(U32);

void PWM_INT(void){
	PINSEL1 |= 1<<8; //P0.21 SEC FUC AS A PWM5
	PWMPCR = 1<<13; //PWM5 IS ENABLE USING PWMPCR 13TH BIT AS A PWMENA5
	PWMMR0 = 60000;
	PWMTCR = 1<<1;	//counter reset
	PWMMCR = 1<<1;	//Reset on PWMMR0
	PWMTCR = 1<<0|1<<3;	//Counter Enable +  PWM Enable
	PWMLER = (1 << 0) | (1 << 1);  // Load the values from MR0 and MR1
}

void PWM(U32 dutyCycle){
	if (dutyCycle <= 100) {
        PWMMR1 = (PWMMR0 * dutyCycle) / 100;  // Calculate and set the duty cycle
        PWMLER = (1 << 1);  // Latch the new MR1 value
    }
}
