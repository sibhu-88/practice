void TIMER0_ISR_CONFIG(U32 *isr_func);
void TIMER1_ISR_CONFIG(U32 *isr_func);
void UART0_ISR_CONFIG(U32 *isr_func);
void UART1_ISR_CONFIG(U32 *isr_func);
void EXT0_ISR_CONFIG(U32 *isr_func);
void EXT1_ISR_CONFIG(U32 *isr_func);
void EXT2_ISR_CONFIG(U32 *isr_func);
void EXT3_ISR_CONFIG(U32 *isr_func);

void TIMER0_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 4);    // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 4;      // Enable and assign Timer 0 interrupt
    VICIntEnable |= (1 << 4);     // Enable Timer 0 interrupt
}

void TIMER1_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 5);    // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 5;      // Enable and assign Timer 1 interrupt
    VICIntEnable |= (1 << 5);     // Enable Timer 1 interrupt
}

void UART0_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 6);    // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 6;      // Enable and assign UART 0 interrupt
    VICIntEnable |= (1 << 6);     // Enable UART 0 interrupt
}

void UART1_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 7);    // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 7;      // Enable and assign UART 1 interrupt
    VICIntEnable |= (1 << 7);     // Enable UART 1 interrupt
}

void EXT0_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 14);   // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 14;     // Enable and assign EINT0 interrupt
    VICIntEnable |= (1 << 14);    // Enable External Interrupt 0
}

void EXT1_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 15);   // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 15;     // Enable and assign EINT1 interrupt
    VICIntEnable |= (1 << 15);    // Enable External Interrupt 1
}

void EXT2_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 16);   // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 16;     // Enable and assign EINT2 interrupt
    VICIntEnable |= (1 << 16);    // Enable External Interrupt 2
}

void EXT3_ISR_CONFIG(U32 *isr_func)
{
    VICIntSelect &= ~(1 << 17);   // Set as IRQ
    VICVectAddr0 = (U32)isr_func; // Assign ISR to vectored slot 0
    VICVectCntl0 = 0x20 | 17;     // Enable and assign EINT3 interrupt
    VICIntEnable |= (1 << 17);    // Enable External Interrupt 3
}
