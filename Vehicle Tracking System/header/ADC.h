void ADC_INIT(void);
unsigned int ADC_Read(void);

void ADC_INIT(void) {
    PINSEL1 |= (1 << 22);  // P0.27 as AD0.1 (ADC channel 1)

    // Configure the ADC settings
    ADCR = (1 << 0)        // Select AD0.0 as the input channel
         | (4 << 8)        // Set the ADC clock divisor (ADC clock = PCLK/5)
         | (1 << 21);      // Enable the ADC
}

unsigned int ADC_Read(void) {
		U32 result;
    ADCR |= (1 << 24);     // Start ADC conversion

    // Wait until conversion is complete (DONE bit in ADDR)
    while (!(ADDR & (1 << 31)));

    // Extract the result (10-bit value from bit 6 to bit 15)
    result = (ADDR >> 6) & 0x3FF;

    return result;         // Return the 10-bit ADC result
}
