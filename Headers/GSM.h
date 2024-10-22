
// Function to send SMS using GSM module
void GSM_SMS(U8 *num1, U8 *msg1, U8 *msg2)
{
    // Initial delay to allow the GSM module to initialize
    delay_milisec(1000);

    // Send "AT" command to test communication with the GSM module
    UART_STR_TX("AT\r\n");
    delay_milisec(1000);

    // Set the GSM module to SMS text mode (CMGF=1)
    UART_STR_TX("AT+CMGF=1\r\n");
    delay_milisec(1000);

    // Send the command to set the recipient phone number
    UART_STR_TX("AT+CMGS=\"");
    UART_STR_TX(num1); // Append the phone number
    UART_STR_TX("\"\r\n");
    delay_milisec(1000);

    // Send the message content (two parts: msg1 and msg2)
    UART_STR_TX(msg1); // Send the first part of the message
    UART_STR_TX(" ");
    UART_STR_TX(msg2); // Send the second part of the message

    // End the message by sending the CTRL+Z (ASCII 0x1A) character
    UART_TX(0x1A);
}
