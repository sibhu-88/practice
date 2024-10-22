#include "A:\Siva\Projects\Headers\typedef.h"
#include "A:\Siva\Projects\Headers\delay.h"
#include <string.h>

// Define LCD control pins and data bits
#define RS 1 << 17    // Register Select pin
#define RW 1 << 18    // Read/Write pin
#define E 1 << 19     // Enable pin
#define LCD 0x0F << 20 // LCD data bits (D4 to D7) mapped to P1.20 to P1.23

// Function Prototypes
void LCD_DATA(void);
void LCD_INIT(void);
void LCD_CMD(U32 cmd);
void LCD_DISPLAY(U32 data);
void LCD_STR(S8 *str);
void LCD_INT(U32 data);
void LCD_FLOAT(F32 value);
void LCD_SCROLL(S8 *str);

void LCD_DATA(void){
	LCD_INIT();
	LCD_DISPLAY('S');
	delay_milisec(2000);
	LCD_CMD(0X01);
	LCD_STR("PRABHU");
	delay_milisec(2000);
	LCD_CMD(0X01);
	LCD_STR("HI PRABHU, HOW ARE YOU, WHERE YOU FROM.");
	delay_milisec(2000);
	LCD_CMD(0X01);
	LCD_INT(88);
	delay_milisec(2000);
	LCD_CMD(0X01);
	LCD_FLOAT(77.08);
	delay_milisec(2000);
	LCD_CMD(0X01);
	LCD_SCROLL("HI PRABHU, HOW ARE YOU, WHERE YOU FROM.");
}

void LCD_INIT(void)
{
    PINSEL2 |= 0;               // Configure pins as GPIO
    IODIR1 |= LCD | RS | RW | E; // Set LCD control and data pins as output
    delay_milisec(20);          // Wait for LCD to power up

    // Initialize the LCD to 4-bit mode
    LCD_CMD(0x02); // Return home
    LCD_CMD(0x28); // 4-bit mode, 2 lines, 5x8 font
    LCD_CMD(0x0C); // Display ON, cursor OFF
    LCD_CMD(0x01); // Clear display
		LCD_CMD(0X80);
    delay_milisec(5);
}

void LCD_CMD(U32 cmd)
{
    // Send higher nibble
    IOCLR1 = LCD;                // Clear LCD data pins
    IOSET1 = (cmd & 0xF0) << 16; // Send high nibble to data pins
    IOCLR1 = RS | RW;            // RS = 0 for command, RW = 0 for write
    IOSET1 = E;                  // Enable pulse
    delay_milisec(1);
    IOCLR1 = E;

    // Send lower nibble
    IOCLR1 = LCD;
    IOSET1 = (cmd & 0x0F) << 20; // Send low nibble to data pins
    IOCLR1 = RS | RW;
    IOSET1 = E;
    delay_milisec(1);
    IOCLR1 = E;
}

void LCD_DISPLAY(U32 data)
{
    // Send higher nibble
    IOCLR1 = LCD;
    IOSET1 = (data & 0xF0) << 16; // Send high nibble to data pins
    IOSET1 = RS;                  // RS = 1 for data
    IOCLR1 = RW;                  // RW = 0 for write
    IOSET1 = E;
    delay_milisec(1);
    IOCLR1 = E;

    // Send lower nibble
    IOCLR1 = LCD;
    IOSET1 = (data & 0x0F) << 20; // Send low nibble to data pins
    IOSET1 = RS;
    IOCLR1 = RW;
    IOSET1 = E;
    delay_milisec(1);
    IOCLR1 = E;
}

void LCD_STR(S8 *str)
{
    U32 cnt = 0;
    while (*str)
    {
        LCD_DISPLAY(*str++);
        cnt++;
        if (cnt == 16)
        {                  // Move to the second line after 16 characters
            LCD_CMD(0xC0); // Command to move cursor to the second line
        }
    }
}

/*
void LCD_STR(S8 *str) {
    U32 cnt = 0;
    S8 *word_start = str;  // Pointer to keep track of the beginning of a word

    while (*str) {
        // If the current character is a space, we can print the word up to this point
        if (*str == ' ' || *(str + 1) == '\0') {
            // Check if the word will fit on the current line
            U32 word_length = str - word_start + 1;  // Length of the word + 1 for the space
            if (cnt + word_length > 16) {            // If the word exceeds the line limit
                LCD_CMD(0xC0);                       // Move to the second line
                cnt = 0;                             // Reset the character count
            }

            // Print the word
            while (word_start <= str) {
                LCD_DISPLAY(*word_start++);
                cnt++;
            }

            if (cnt == 16) {  // Move to the next line if the limit is reached
                LCD_CMD(0xC0);
                cnt = 0;
            }

            word_start++;  // Skip the space and move to the next word
        }

        str++;  // Continue to the next character
    }
}

*/

void LCD_INT(U32 data)
{
    char buf[10]; // Buffer to hold the string representation
    U32 i = 0;    // Index for the buffer

    // Handle zero explicitly
    if (data == 0)
    {
        LCD_DISPLAY('0'); // Directly display '0' on the LCD
        return;
    }

    // Check for negative numbers (if you want to handle negatives)
    if (data < 0)
    {
        LCD_DISPLAY('-'); // Display negative sign
        data = -data;     // Make data positive
    }

    // Extract digits in reverse order
    while (data > 0)
    {
        buf[i++] = (data % 10) + '0'; // Convert digit to character and store in buffer
        data /= 10;                   // Remove the last digit
    }

    // Display the digits in correct order
    while (i > 0)
    {
        LCD_DISPLAY(buf[--i]); // Display from the end of the buffer
    }
}

void LCD_FLOAT(F32 value)
{
    U32 integer_part = (U32)value;           // Extract integer part
    F32 decimal_part = value - integer_part; // Extract decimal part

    LCD_INT(integer_part); // Display integer part
    LCD_DISPLAY('.');      // Display decimal point

    decimal_part *= 100;        // Shift two decimal places
    LCD_INT((U32)decimal_part); // Display fractional part
}

// void LCD_SCROLL(S8 *str)
// {
//     U32 length = strlen(str); // Get the length of the string
//     U32 display_length = 16;  // Length of the LCD display (assuming 16x2 LCD)

//     // Create a buffer with extra spaces for scrolling
//     S8 scroll_str[30]; // Adjust size based on expected string length
//     U32 i, j;

//     // Initialize the buffer with the original string followed by spaces
//     for (i = 0; i < length; i++)
//     {
//         scroll_str[i] = str[i];
//     }
//     // Fill the rest of the buffer with spaces
//     for (; i < sizeof(scroll_str) - 1; i++)
//     {
//         scroll_str[i] = ' ';
//     }
//     scroll_str[i] = '\0'; // Null-terminate the string

//     // Scroll through the string
//     for (i = 0; i < length + display_length; i++)
//     {
//         LCD_CMD(0x01); // Clear display
//         for (j = 0; j < display_length; j++)
//         {
//             // Display the character at the current index
//             LCD_DISPLAY(scroll_str[i + j]); // Show one character at a time
//         }
//         delay_milisec(300); // Adjust the delay for scrolling speed
//     }
// }

void LCD_SCROLL(char* msg) {
    int i, len = strlen(msg);

    for (i = 0; i < len; i++) {
        LCD_CMD(0x80); // Set cursor to the beginning
        LCD_STR(msg + i); // Display from i-th character onwards
        delay_milisec(300);

        if (len - i < 16) {
            LCD_CMD(0x80); // Set cursor to the beginning
            LCD_STR(msg);
            delay_milisec(300);
        }
    }
}
