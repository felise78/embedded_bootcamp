#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RED_PIN     PD5
#define GREEN_PIN   PD6
#define BLUE_PIN    PD3

#define SET_PIN_HIGH(port, pin)     (port |= (1 << pin))
#define SET_PIN_LOW(port, pin)      (port &= ~(1 << pin))

void init_RGB_LED()
{
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN); // Set pins as output
    PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN)); // Set pins low initially
}

void set_RGB_color(uint8_t red, uint8_t green, uint8_t blue) {

    if (red)
        SET_PIN_HIGH(PORTD, RED_PIN);
    else
        SET_PIN_LOW(PORTD, RED_PIN);
    
    if (green)
        SET_PIN_HIGH(PORTD, GREEN_PIN);
    else
        SET_PIN_LOW(PORTD, GREEN_PIN);
    
    if (blue)
        SET_PIN_HIGH(PORTD, BLUE_PIN);
    else
        SET_PIN_LOW(PORTD, BLUE_PIN);
}


int main ()
{
    init_RGB_LED();
    
       while (1) {
        // rouge
        set_RGB_color(0xFF, 0x00, 0x00);
        _delay_ms(1000);
        
        // vert
        set_RGB_color(0x00, 0xFF, 0x00);
        _delay_ms(1000);
        
        // bleu
        set_RGB_color(0x00, 0x00, 0xFF);
        _delay_ms(1000);
        
        // jaune
        set_RGB_color(0xFF, 0xFF, 0x00);
        _delay_ms(1000);
        
        // cyan
        set_RGB_color(0x00, 0xFF, 0xFF);
        _delay_ms(1000);
        
        // magenta
        set_RGB_color(0xFF, 0x00, 0xFF);
        _delay_ms(1000);
        
        // blanc
        set_RGB_color(0xFF, 0xFF, 0xFF);
        _delay_ms(1000);
    }
   
    return 0;
}
