#include "main.h"

// void wheel(uint8_t pos) {
//     pos = 255 - pos;
//     if (pos < 85) {
//         set_rgb(255 - pos * 3, 0, pos * 3);
//     } else if (pos < 170) {
//         pos = pos - 85;
//         set_rgb(0, pos * 3, 255 - pos * 3);
//     } else {
//         pos = pos - 170;
//         set_rgb(pos * 3, 255 - pos * 3, 0);
//     }
// }

union
{
    struct {
        uint8_t br;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    }s;
    uint32_t col;
}a;

void set_LEDS(char* color, bool rainbow)
{
    if (rainbow)
    {
        uart_printstr("\x1b[2J\x1b[H");
        uart_printstr("Rainbow wheel interruption\r\n");
        return;
    }
    // or SET LED D6 / D7 / D8
    //struct apa a;
    a.s.br = 0xFF;
    a.s.r = hexToDec(color[1], color[2]);
    uart_tx(' ');
    print_number(a.s.r);
    uart_tx(' ');
    a.s.g = hexToDec(color[3], color[4]);
    print_number(a.s.g);
    uart_tx(' ');
    a.s.b = hexToDec(color[5], color[6]);
    print_number(a.s.b);

//     union {
//         char format[8];
//         uint32_t led;
//     } col;
//    // char format[8];
//     col.format[0] = 'F';
//     col.format[1] = 'F';
//     for (int i = 2; i < 8; ++i)
//         col.format[i] = color[i - 1];
    //col.format[8] = '\0';
    // uart_printstr("format : ");
    // uart_printstr(col.format);
    // uart_printstr("\r\n");
    // uart_printstr("led :");
    // print_number(col.led);
    // uart_printstr("\r\n");
    if (color[8] == '6')
        SPI_set_LEDS(a.col, LED_OFF, LED_OFF);
    else if (color[8] == '7')
        SPI_set_LEDS(LED_OFF, a.col, LED_OFF);
    else if (color[8] == '8')
        SPI_set_LEDS(LED_OFF, LED_OFF, a.col);
    return;
}

int main ()
{
    SPI_init();
    uart_init();
    _delay_ms(100);
    uart_printstr("Enter a value #RRGGBBDD : \r\n");
    char color[MAX];
    for(int i = 0; i < MAX; i++)
        color[i] = 0;
    int i = 0;
    while (1)
    {
        char c = uart_rx();
        if (c != 0 && i < MAX)
        {
            if (c == '\r')
            {   
                // uart_printstr(color); // DEBUG
                if (strcmp_cheatcode(color))
                {
                    uart_printstr("cheatcode ok\r\n");
                    set_LEDS("", 1);
                }
                else if (parse(color) && i < 10)
                {
                    //uart_printstr("format ok\r\n");
                    set_LEDS(color, 0);
                }
                else
                {
                    uart_printstr("\x1b[2J\x1b[H");
                    uart_printstr("Error : Input is incorrect : ");
                    for(int j = 0; j < i; j++)
                    {
                        uart_tx(color[j]);
                    }
                    uart_printstr("\r\n");
                    _delay_ms(1500);
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
            uart_printstr("Error : Input is too long\r\n");
            _delay_ms(1500);
            uart_printstr("\x1b[2J\x1b[H");
            uart_printstr("Enter a value #RRGGBBDD : \r\n");
            i = 0;
        }
        _delay_ms(20);
    }
    return 0;
}

// struct apa {
    
//     union {
//         struct {
//             uint8_t bit : 3;
//             uint8_t global : 5;
//         } b;
//         uint8_t g;
//     } u;
  
//     uint8_t r;
//     uint8_t g;
//     uint8_t b;
    
// };

// struct apa a;
// a.u.g
// a.r
// a.g

// a.u.b.bit = 0b111;

// a.global = 12;