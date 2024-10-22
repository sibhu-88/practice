// Define pin functions for SPI communication
#define SCK (1 << 8)   // SCK pin (P0.8)
#define MISO (1 << 10) // MISO pin (P0.10)
#define MOSI (1 << 12) // MOSI pin (P0.12)

// Define the Chip Select (CS) pin
#define CS_PIN (1 << 7) // Chip Select (P0.7)

// Clock and Baud Rate configuration
#define FOSC 12000000                   // Oscillator Frequency (12 MHz)
#define CCLK (5 * FOSC)                 // Core Clock Frequency
#define PCLK (CCLK / 4)                 // Peripheral Clock Frequency
#define SPCCR_VAL 60                    // SPI Clock Prescaler value
#define SPI_RATE (U8)(PCLK / SPCCR_VAL) // SPI clock rate

// SPI Control Register (SPCR) Mode Settings
#define MODE_0 0x00 // CPOL 0, CPHA 0 (SPI Mode 0)
#define MODE_1 0x08 // CPOL 0, CPHA 1 (SPI Mode 1)
#define MODE_2 0x10 // CPOL 1, CPHA 0 (SPI Mode 2)
#define MODE_3 0x18 // CPOL 1, CPHA 1 (SPI Mode 3)

// SPI Control Register Bits
#define MSTR_BIT 5 // Master mode bit
#define LSBF_BIT 6 // Least Significant Bit first (default MSB first)
#define SPIE_BIT 7 // SPI Interrupt Enable bit

// SPI Status Register (SPSR) Bits
#define SPIF_BIT 7 // SPI Transfer Completion flag

// SPI Interrupt Register Bit
#define SPIINTF_BIT 0 // SPI Interrupt flag bit

// SPI Master Initialization
void SPI_MASTER_INIT()
{
    // Configure the pins for SPI function
    PINSEL0 |= SCK | MISO | MOSI;

    // Set SPI clock rate and initialize in Master Mode with Mode 3 (CPOL = 1, CPHA = 1)
    S0SPCCR = SPI_RATE;
    S0SPCR = (1 << MSTR_BIT) | MODE_3;

    // Configure Chip Select (CS) pin as output and set it high (inactive)
    IODIR0 |= CS_PIN;
    IOSET0 = CS_PIN; // Set CS high
}

// SPI Data Transmission and Reception (Full-Duplex)
U8 SPI_TRANSFER(U8 data)
{
    // Clear the SPIF flag by reading the status register
    U8 status = S0SPSR;

    // Load the data to be transmitted into the SPI Data Register (S0SPDR)
    S0SPDR = data;

    // Wait for the transmission to complete (SPIF bit is set)
    while (!(S0SPSR & (1 << SPIF_BIT)))
        ;

    // Return the received data from SPI Data Register
    return S0SPDR;
}

// SPI Transfer with Chip Select Management
U8 SPI_TRANSFER_WITH_CS(U8 data)
{
		// Transfer data over SPI
    U8 received_data = SPI_TRANSFER(data);
		
    // Assert CS (set it low to select the slave)
    IOCLR0 = CS_PIN;

    // Deassert CS (set it high to deselect the slave)
    IOSET0 = CS_PIN;

    // Return the received data
    return received_data;
}
