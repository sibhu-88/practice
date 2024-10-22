
// Define pin functions for I2C communication
#define SCL_EN (1 << 4) // P0.4 for SCL (Serial Clock Line)
#define SDA_EN (1 << 6) // P0.6 for SDA (Serial Data Line)

// Define I2C speed and related constants
#define CCLK 60000000                    // CPU Clock Frequency in Hz
#define PCLK (CCLK / 4)                  // Peripheral Clock Frequency in Hz
#define I2C_SPEED 100000                 // I2C Speed in Hz
#define LOADVAL ((PCLK / I2C_SPEED) / 2) // Load value for SCL frequency

// Bit defines for I2CONSET register
#define AA_BIT 2   // Acknowledge flag
#define SI_BIT 3   // Interrupt flag
#define STO_BIT 4  // Stop flag
#define STA_BIT 5  // Start flag
#define I2EN_BIT 6 // I2C Enable flag

// Initialize I2C communication
void I2C_INIT()
{
    PINSEL0 |= SCL_EN | SDA_EN; // Set SCL and SDA pins for I2C function
    I2CONSET = (1 << I2EN_BIT); // Enable I2C
    I2SCLL = LOADVAL;           // Set low period of SCL clock
    I2SCLH = LOADVAL;           // Set high period of SCL clock
}

// Send a Start condition
void I2C_START()
{
    I2CONSET = (1 << STA_BIT); // Set Start flag
    while (!((I2CONSET >> SI_BIT) & 1))
        ;                      // Wait for SI bit to be set
    I2CONCLR = (1 << STA_BIT); // Clear Start flag
}

// Send a Repeated Start condition
void I2C_RESTART()
{
    I2CONSET = (1 << STA_BIT); // Set Start flag
    I2CONCLR = (1 << SI_BIT);  // Clear SI bit to acknowledge
    while (!((I2CONSET >> SI_BIT) & 1))
        ;                      // Wait for SI bit to be set
    I2CONCLR = (1 << STA_BIT); // Clear Start flag
}

// Write data to I2C bus
void I2C_WRITE(U8 DATA)
{
    I2DAT = DATA;             // Load data into I2DAT register
    I2CONCLR = (1 << SI_BIT); // Clear SI bit to send data
    while (!((I2CONSET >> SI_BIT) & 1))
        ; // Wait for SI bit to be set
}

// Send a Not Acknowledge response
U8 I2C_NACK()
{
    I2CONCLR = (1 << SI_BIT); // Clear SI bit to acknowledge
    while (!((I2CONSET >> SI_BIT) & 1))
        ;         // Wait for SI bit to be set
    return I2DAT; // Return received data
}

// Send an Acknowledge response
U8 I2C_MASTERACK(void)
{
    I2CONSET = (1 << AA_BIT); // Set Acknowledge flag
    I2CONCLR = (1 << SI_BIT); // Clear SI bit to acknowledge
    while (!((I2CONSET >> SI_BIT) & 1))
        ;                     // Wait for SI bit to be set
    I2CONCLR = (1 << AA_BIT); // Clear Acknowledge flag
    return I2DAT;             // Return received data
}

// Send a Stop condition
void I2C_STOP(void)
{
    I2CONSET = (1 << STO_BIT); // Set Stop flag
    I2CONCLR = (1 << SI_BIT);  // Clear SI bit
    while ((I2CONSET >> STO_BIT) & 1)
        ; // Wait for Stop condition to be acknowledged
}
