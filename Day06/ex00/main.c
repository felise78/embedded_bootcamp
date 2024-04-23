#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define RED_PIN     PB5
#define GREEN_PIN   PB6
#define BLUE_PIN    PB3

void init_RGB_LED()
{
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN); // Set pins as output
    PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN)); // Set pins low initially
}

void turn_on_red() {
    PORTD |= (1 << RED_PIN);
    PORTD &= ~((1 << GREEN_PIN) | (1 << BLUE_PIN));
}

void turn_on_green() {
    PORTD |= (1 << GREEN_PIN);
    PORTD &= ~((1 << RED_PIN) | (1 << BLUE_PIN));
}


void turn_on_blue() {
    PORTD |= (1 << BLUE_PIN);
    PORTD &= ~((1 << RED_PIN) | (1 << GREEN_PIN));
}

int main ()
{
    init_RGB_LED();

    while (1)
    {
        turn_on_red(); // Turn on red LED
        _delay_ms(1000); // Delay 1 second

        turn_on_green(); // Turn on green LED
        _delay_ms(1000); // Delay 1 second

        turn_on_blue(); // Turn on blue LED
        _delay_ms(1000); // Delay 1 second
    }
   
    return 0;
}
