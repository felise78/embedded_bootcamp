#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SPI_SS      PB2
#define SPI_MOSI    PB3
#define SPI_MISO    PB4
#define SPI_SCK     PB5


#define LED_ON      0xFFFFFFFF
#define LED_OFF     0xFF000000

// Init the SPI as master, MOSI/SCK/SS pins as outputs.
static inline void SPI_init(void)
{
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

	/* Enable SPI master mode + prescaler of 64 */
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char data) 
{
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

static inline void spi_send_32(uint32_t data)
{
	SPI_MasterTransmit((uint8_t)(data >> 24));
	SPI_MasterTransmit((uint8_t)(data >> 16));
	SPI_MasterTransmit((uint8_t)(data >> 8));
	SPI_MasterTransmit((uint8_t)data);
}

static inline void SPI_set_LEDS(uint32_t led1, uint32_t led2, uint32_t led3)
{

	spi_send_32(0);
    spi_send_32(led1);
    spi_send_32(led2);
    spi_send_32(led3);
	spi_send_32(0xFFFFFFFF);
	
}

int main(void)
{
    SPI_init();

    while (1) 
    {
        SPI_set_LEDS(LED_ON, LED_OFF, LED_OFF);         
        _delay_ms(250);
        SPI_set_LEDS(LED_OFF, LED_ON, LED_OFF);         
        _delay_ms(250);
        SPI_set_LEDS(LED_OFF, LED_OFF, LED_ON);         
        _delay_ms(250);
        SPI_set_LEDS(LED_OFF, LED_OFF, LED_OFF);
        _delay_ms(250);
    } 
    
    return 0;
}
