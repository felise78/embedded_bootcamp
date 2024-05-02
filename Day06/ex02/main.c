#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define RED_PIN     PD5     // OC0B
#define GREEN_PIN   PD6     // OC0A
#define BLUE_PIN    PD3     // OC2B


void init_rgb()
{
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN); // Set pins as output
    PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN)); // Set pins low initially

    // set les timers
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS00); // Mode 3, pas de prescaleur

    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS20); // Mode Fast PWM, pas de préscaleur
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {

    OCR0A = g;  
    OCR0B = r;  
    OCR2B = b;

}

void wheel(uint8_t pos) {
    pos = 255 - pos;
    if (pos < 85) {
        set_rgb(255 - pos * 3, 0, pos * 3);
    } else if (pos < 170) {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    } else {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

void display_color_wheel() {
    
    uint8_t pos = 0;

    while (1) {
        wheel(pos);
        pos = (pos + 1) % 256; // 255 + 0
        _delay_ms(10);
    }
}

int main ()
{
    init_rgb();
    display_color_wheel();
    return 0;
}
