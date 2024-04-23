#include "main.h"


#define RED_PIN     PD5     // OC0B
#define GREEN_PIN   PD6     // OC0A
#define BLUE_PIN    PD3     // OC2B

#define SET_PIN_HIGH(port, pin)     (port |= (1 << pin))
#define SET_PIN_LOW(port, pin)      (port &= ~(1 << pin))

void init_rgb()
{
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN); // Set pins as output
    PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN)); // Set pins low initially

    // set les timers
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << WGM02) | (1 << CS00); // Mode 15, pas de préscaleur (fast PWM)
    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS20); // Mode PWM, pas de préscaleur (fast PWM)
}

void print_hex_value(unsigned char c) {

	//unsigned char c = c;
	static char buffer[3] = { '0', '0', '\0'};
    int i =  sizeof(buffer) - 1;
	do {
		buffer[--i] = "0123456789ABCDEF"[c & 0x0f];
		c >>= 4;
	} while (c);
	uart_printstr(buffer);
}

// void separate_colors(void *ptr)
// {
//     char *color = (char *)ptr;
//     uart_printstr(color);
//     unsigned char r = strtol(color + 1, NULL, 16);
//     unsigned char g = strtol(color + 3, NULL, 16);
//     unsigned char b = strtol(color + 5, NULL, 16);
//     uart_printstr("Red : ");
//     print_hex_value(r);
//     uart_printstr("\r\n");
//     uart_printstr("Green : ");
//     print_hex_value(g);
//     uart_printstr("\r\n");
//     uart_printstr("Blue : ");
//     print_hex_value(b);
//     uart_printstr("\r\n");
// }

void extract_colors(const char *color) {

    // char **end_r = (char **)(color + 3); 
    // char **end_g = (char **)(color + 5); 
    // char **end_b = (char **)(color + 7);
    // char r[2];
    // r[0] = color[1];
    // r[1] = color[2];
    // char g[2];
    // g[0] = color[3];
    // g[1] = color[4];
    // char b[2];
    // b[0] = color[5];
    // b[1] = color[6];

    // uart_printstr("Red : ");
    // uart_printstr(r);
    // uart_printstr("\r\n");
    // uart_printstr("Green : ");
    // uart_printstr(g);
    // uart_printstr("\r\n");
    // uart_printstr("Blue : ");
    // uart_printstr(b);
    // uart_printstr("\r\n");
    char *endPtr;

    uint8_t r = (uint8_t)strtol(color + 1, &endPtr, 16);
    uint8_t g = (uint8_t)strtol(color + 3, &endPtr, 16);
    uint8_t b = (uint8_t)strtol(color + 5, &endPtr, 16);
    uart_printstr("Red : ");
    print_hex_value(r);
    uart_printstr("\r\n");
    uart_printstr("Green : ");
    print_hex_value(g);
    uart_printstr("\r\n");
    uart_printstr("Blue : ");
    print_hex_value(b);
    uart_printstr("\r\n");
}

bool parse(char *color)
{
    int i = 0;
    if (color[0] != '#')
        return false;
    while (++i < 7)
    {
        if ((color[i] < '0' || (color[i] > '9' && color[i] < 'A') || color[i] > 'F'))
            return false;
    }
    return true;
}

int main ()
{
    init_rgb();
    uart_init();

    uart_printstr("Enter a HEX RGB value, format #RRGGBB : \r\n");
    char color[8];
    int i = 0;
    while (1)
    {
        char c = uart_rx();
        if (c != 0 && i < 8)
        {
            uart_tx(c);
            color[i] = c;
            i++;
        }
        if (i == 8)
        {
            uart_printstr("\r\n");
            if (parse(color))
            {
                uart_printstr("format ok\r\n");
                //uint8_t r = 0, g = 0, b = 0;
                extract_colors(color);
                // uart_printstr("Red : ");
                // print_hex_value(r);
                // uart_printstr("\r\n");
                // uart_printstr("Green : ");
                // print_hex_value(g);
                // uart_printstr("\r\n");
                // uart_printstr("Blue : ");
                // print_hex_value(b);
                // uart_printstr("\r\n");
            }
            else
            {
                uart_printstr("format pas ok\r\n");
                uart_printstr("Enter a HEX RGB value, format #RRGGBB : \r\n");
                i = 0;
            }
        }
    }
    return 0;
}
