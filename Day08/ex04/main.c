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


int main ()
{
    SPI_init();
    uart_init();
    _delay_ms(100);
    uart_printstr("Enter a value #RRGGBBDD : \r\n");
    char color[MAX];
    int i = 0;
    while (1)
    {
        char c = uart_rx();
        if (c != 0 && i < MAX)
        {
            if (c == '\r')
            {   
                uart_printstr("rentre ici\r\n");
                uart_printstr(color);
                uart_tx(color[MAX - 1] + 48);
                
                if (strcmp_cheatcode(color))
                {
                    uart_printstr("cheatcode ok\r\n");
                    // programme
                }
                else
                {
                    uart_printstr("\x1b[2J\x1b[H");
                    uart_printstr("Enter a value #RRGGBBDD : \r\n");
                    i = 0;
                }
            }
            else
            {
                uart_tx(c);
                color[i] = c;
                i++;
            }
        }
        if (i == MAX)
        {
            uart_printstr("\x1b[2J\x1b[H");
            uart_printstr("Enter a value #RRGGBBDD : \r\n");
            i = 0;
        }
        _delay_ms(20);
    }
    return 0;
}

// int main ()
// {
//     _delay_ms(100);
//     uart_init();
//     uart_printstr("Enter a value #RRGGBBDD : \r\n");
//     char color[MAX];
//     int i = 0;
//     while (1)
//     {
//         char c = uart_rx();
//         if (c != 0 && i < MAX)
//         {
//             if (c == '\r')
//             {
//                 if (parse(color))
//                 {
//                     uart_printstr("format ok");
//                     // programme
//                 }
//                 else
//                 {
//                     uart_printstr("\x1b[2J\x1b[H");
//                     uart_printstr("Enter a value #RRGGBBDD : \r\n");
//                     i = 0;
//                 }
//             }
//             else
//             {
//                 uart_tx(c);
//                 color[i] = c;
//                 i++;
//             }
//         }
//         if (i == MAX)
//         {
//             uart_printstr("\x1b[2J\x1b[H");
//             uart_printstr("Enter a value #RRGGBBDD : \r\n");
//             i = 0;
//         }
//     }
//     return 0;
// }