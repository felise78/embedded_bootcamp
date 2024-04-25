#include "main.h"

#define SPI_SS      PB2
#define SPI_MOSI    PB3
#define SPI_MISO    PB4
#define SPI_SCK     PB5

#define LED_ON      0xFFFFFFFF
#define LED_OFF     0xFF000000

// Init the SPI as master, MOSI/SCK/SS pins as outputs.
void SPI_init(void)
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

void spi_send_32(uint32_t data)
{
	SPI_MasterTransmit((uint8_t)(data >> 24));
	SPI_MasterTransmit((uint8_t)(data >> 16));
	SPI_MasterTransmit((uint8_t)(data >> 8));
	SPI_MasterTransmit((uint8_t)data);
}

void SPI_set_LEDS(uint32_t led1, uint32_t led2, uint32_t led3)
{

	spi_send_32(0);
    spi_send_32(led1);
    spi_send_32(led2);
    spi_send_32(led3);
	spi_send_32(0xFFFFFFFF);
	
}

void convert_LED(uint8_t adc_value)
{
    if (adc_value <= 84)
        SPI_set_LEDS(LED_OFF, LED_OFF, LED_OFF);
    else if (adc_value <= 169)
        SPI_set_LEDS(LED_ON, LED_OFF, LED_OFF);
    else if (adc_value <= 254)
        SPI_set_LEDS(LED_ON, LED_ON, LED_OFF);
    else
        SPI_set_LEDS(LED_ON, LED_ON, LED_ON);
}

int main(void)
{
    SPI_init();
    ADC_init();

    while (1) 
    {
        uint8_t adc_value = ADC_read(PC0);
        _delay_ms(20);
        convert_LED(adc_value);
    } 
    
    return 0;
}
