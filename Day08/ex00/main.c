#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SPI_SS      PB2
#define SPI_MOSI    PB3
#define SPI_MISO    PB4
#define SPI_SCK     PB5

#define PADDING_BITS (0xFF)

#define LED_OFF (0)

/* Levels of brightness */
#define B_LOW (0x01000000)
#define B_MED (0x08000000)
#define B_HIGH (0x1F000000)

/* LED colors */
#define RED (0xFF0000)
#define GREEN (0x00FF00)
#define BLUE (0x0000FF)
#define YELLOW (0xFFFF00)
#define CYAN (0x00FFFF)
#define WHITE (0xFFFFFF)

// Init the SPI as master, MOSI/SCK/SS pins as outputs.
static inline void SPI_init(void)
{
    DDRB = 0;
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
    PORTB = 0;
	/* Enable SPI master mode + prescaler of 64 */
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char data) //Send a byte of data through MOSI.
{
    SPDR = data;
    // Attendre la fin de la transmission
    while(!(SPSR & (1<<SPIF)));
}

static inline void spi_send_32(uint32_t data)
{
	SPI_MasterTransmit((uint8_t)(data >> 24));
	SPI_MasterTransmit((uint8_t)(data >> 16));
	SPI_MasterTransmit((uint8_t)(data >> 8));
	SPI_MasterTransmit((uint8_t)data);
}

static inline void SPI_set_LEDS()
{
	spi_send_32(0);             // start SPI transfer
    // LED D6
    SPI_MasterTransmit(0xFF);   // Brightness + start bit
    SPI_MasterTransmit(0x00);   // Bleu
    SPI_MasterTransmit(0x00);   // Vert
    SPI_MasterTransmit(0xFF);   // Rouge
    // LED D7
    SPI_MasterTransmit(0xFF);   // Brightness + start bit
    SPI_MasterTransmit(0x00);   // Bleu
    SPI_MasterTransmit(0x00);   // Vert
    SPI_MasterTransmit(0x00); 
    // LED D8
    SPI_MasterTransmit(0xFF);   // Brightness + start bit
    SPI_MasterTransmit(0x00);   // Bleu
    SPI_MasterTransmit(0x00);   // Vert
    SPI_MasterTransmit(0x00); 

	spi_send_32(0xFFFFFFFF);    // stop SPI transfer
}

int main(void)
{
    SPI_init();
    SPI_set_LEDS();
    
    return 0;
}
