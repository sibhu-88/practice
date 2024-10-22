
// UART function prototypes
void UART_INIT(void);
void UART_TX(U32 data);
void UART_RX(U8 *data);
void UART_STR_TX(U8 *str);
void UART_STR_RX(U8 *str);

void UART_INIT(void)
{
    // Configure pins for UART0 (P0.0 for TXD, P0.1 for RXD)
    PINSEL0 |= 0x05; // Set P0.0 as TXD and P0.1 as RXD

    // Configure UART0 for 9600 baud rate, 8 data bits, no parity, 1 stop bit
    U0LCR = 0x83; // Enable DLAB (Divisor Latch Access Bit)
    U0DLM = 0x00; // Set Divisor Latch MSB to 0
    U0DLL = 0x61; // Set Divisor Latch LSB for 9600 baud rate (assuming 15 MHz clock)
    U0LCR = 0x03; // Disable DLAB, 8-bit data, 1 stop bit, no parity
}

void UART_TX(U32 data)
{
    U0THR = data; // Load data into Transmit Holding Register (THR)
    while (((U0LSR >> 5) & 1) == 0)
        ; // Wait until THR is empty (bit 5 in LSR)
}

void UART_RX(U8 *data)
{
    while ((U0LSR & 1) == 0)
        ;          // Wait until data is received (bit 0 in LSR)
    *data = U0RBR; // Read received data from Receiver Buffer Register (RBR)
}

void UART_STR_TX(U8 *str)
{
    while (*str)
    {
        UART_TX(*str++); // Transmit each character of the string
    }
}

void UART_STR_RX(U8 *str)
{
    U8 received_char;
    do
    {
        UART_RX(&received_char); // Receive each character
        *str++ = received_char;  // Store the received character in the string
    } while (received_char != '\r'); // Stop at carriage return ('\r')
    *str = '\0'; // Null-terminate the string
}
