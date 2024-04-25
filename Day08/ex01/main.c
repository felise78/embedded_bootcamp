#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SPI_SS      PB2
#define SPI_MOSI    PB3
#define SPI_MISO    PB4
#define SPI_SCK     PB5

#define BRIGHTNESS (0xFF)

// Init the SPI as master, MOSI/SCK/SS pins as outputs.
static inline void SPI_init(void)
{
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

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

static inline void SPI_set_D6(uint8_t r, uint8_t g, uint8_t b)
{

	spi_send_32(0);             // start SPI transfer
    // LED D6
    SPI_MasterTransmit(BRIGHTNESS);          // Brightness + start bit
    SPI_MasterTransmit(b);                   // Bleu
    SPI_MasterTransmit(g);                   // Vert
    SPI_MasterTransmit(r);                   // Rouge
    // LED D7
    SPI_MasterTransmit(BRIGHTNESS);   // Brightness + start bit
    SPI_MasterTransmit(0);                 // Bleu
    SPI_MasterTransmit(0);            // Vert
    SPI_MasterTransmit(0); 
    // LED D8
    SPI_MasterTransmit(BRIGHTNESS);     // Brightness + start bit
    SPI_MasterTransmit(0);              // Bleu
    SPI_MasterTransmit(0);              // Vert
    SPI_MasterTransmit(0); 

	spi_send_32(0xFFFFFFFF);            // stop SPI transfer
	
}

int main(void)
{
    SPI_init();

    while (1) 
    {
        SPI_set_D6(0xff, 0, 0);         // rouge
        _delay_ms(1000);
        SPI_set_D6(0, 0xff, 0);         // vert 
        _delay_ms(1000);
        SPI_set_D6(0, 0, 0xff);         // bleu
        _delay_ms(1000);
        SPI_set_D6(0xff, 0xff, 0);      // jaune    
        _delay_ms(1000);
        SPI_set_D6(0, 0xff, 0xff);      // cyan
        _delay_ms(1000);
        SPI_set_D6(0xff, 0, 0xff);      // magenta
        _delay_ms(1000);
        SPI_set_D6(0xff, 0xff, 0xff);   // blanc
        _delay_ms(1000);
    } 
    
    return 0;
}
