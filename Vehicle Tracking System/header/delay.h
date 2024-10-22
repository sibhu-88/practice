// implementing delay functions for seconds, milliseconds, and microseconds using a timer register (presumably for an ARM or other microcontroller)

delay_sec(U32 sec)
{
    T0PR = 15000000 - 1; // Set the prescaler to generate a 1-second delay (assuming 15 MHz clock)
    T0TCR = 0x02;        // Reset the timer
    T0TCR = 0x01;        // Start the timer
    while (T0TC < sec)
        ;         // Wait until the timer counter reaches the desired delay (in seconds)
    T0TCR = 0x00; // Stop the timer
}

delay_milisec(U32 milisec)
{
    T0PR = 15000 - 1; // Set the prescaler to generate a 1-millisecond delay
    T0TCR = 0x02;     // Reset the timer
    T0TCR = 0x01;     // Start the timer
    while (T0TC < milisec)
        ;         // Wait until the timer counter reaches the desired delay (in milliseconds)
    T0TCR = 0x00; // Stop the timer
}

delay_micsec(U32 micsec)
{
    T0PR = 15 - 1; // Set the prescaler to generate a 1-microsecond delay
    T0TCR = 0x02;  // Reset the timer
    T0TCR = 0x01;  // Start the timer
    while (T0TC < micsec)
        ;         // Wait until the timer counter reaches the desired delay (in microseconds)
    T0TCR = 0x00; // Stop the timer
}
