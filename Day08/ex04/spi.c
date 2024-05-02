#include "main.h"

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