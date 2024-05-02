#include "main.h"

#define RED_PIN     PD5     // OC0B
#define GREEN_PIN   PD6     // OC0A
#define BLUE_PIN    PD3     // OC2B

// #define SET_PIN_HIGH(port, pin)     (port |= (1 << pin))
// #define SET_PIN_LOW(port, pin)      (port &= ~(1 << pin))

typedef struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

void init_rgb()
{
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN); // Set pins as output
    //PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN)); // Set pins low initially

    // set les timers
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS00); // Mode 15, pas de préscaleur (fast PWM)
    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS20); // Mode PWM, pas de préscaleur (fast PWM)
    OCR0A = 0;
    OCR0B = 0;  
    OCR2B = 0;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {

    OCR0A = g;  
    OCR0B = r;  
    OCR2B = b;

}

uint8_t hex_char_to_int(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f')
        return 10 + (c - 'a');
    return 0; // Ajouter une gestion d'erreur si nécessaire
}

rgb_t hex_to_rgb(char* hex) {

    char r[2] = {hex[1], hex[2]};
    char g[2] = {hex[3], hex[4]};
    char b[2] = {hex[5], hex[6]};

    rgb_t color;

    // hex str to int
    color.r = hex_char_to_int(r[0]) * 16 + hex_char_to_int(r[1]);
    color.g = hex_char_to_int(g[0]) * 16 + hex_char_to_int(g[1]);
    color.b = hex_char_to_int(b[0]) * 16 + hex_char_to_int(b[1]);

    return color;
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
    _delay_ms(100);
    uart_init();

    set_rgb(0, 0, 0);
    uart_printstr("Enter a HEX RGB value, format #RRGGBB : \r\n");
    char color[8];
    int i = 0;
    while (1)
    {
        char c = uart_rx();
        if (c != 0 && i < 8)
        {
            if ((c == 13 || c == 127) && i < 7)
            {
                uart_printstr("\x1b[2J\x1b[H");
                uart_printstr("Enter a HEX RGB value, format #RRGGBB : \r\n");
                i = 0;
            }
            if ((c >= 32 && c != 127) || c == 13)
            {
                uart_tx(c);
                color[i] = c;
                i++;
            }
        }
        if (i == 8)
        {
            uart_printstr("\x1b[2J\x1b[H");
            if (parse(color))
            {
                rgb_t final = hex_to_rgb(color);
                init_rgb();
                set_rgb(final.r, final.g, final.b);
            }
            uart_printstr("Enter a HEX RGB value, format #RRGGBB : \r\n");
            i = 0;
        }
    }
    return 0;
}
