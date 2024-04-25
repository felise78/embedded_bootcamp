#include "main.h"

// ---------- INIT ---------- //

void ADC_init() {
    
    // Set REFS1:0 bits to select AVCC as reference voltage
    // ADLAR : mettre le bit a 1 pour avoir le resultat sur 8bits 
    ADMUX = (1 << REFS0)| (1 << ADLAR);
    
    // Configure ADC with 8-bit resolution
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); 

}

void init_rgb()
{
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD3); // Set pins as output

    // set les timers
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS00); // Mode 15, pas de préscaleur (fast PWM)

    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (1 << CS20); // Mode PWM, pas de préscaleur (fast PWM)
}


void init_leds()
{
     DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4));
}

// ------------------------ //

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {

    OCR0A = g;  
    OCR0B = r;  
    OCR2B = b;

}

uint8_t ADC_read(uint8_t channel) {
    // Select ADC channel
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    
    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    // Return 8-bit ADC value
    return ADCH;
}

// void print_hex_value(unsigned char titouan) {

// 	char buffer[3] = { '0', '0', '\0'};
//     int i =  sizeof(buffer) - 1;
// 	do {
// 		buffer[--i] = "0123456789ABCDEF"[titouan & 0x0f];
// 		titouan >>= 4;
// 	} while (titouan);
// 	uart_printstr(buffer);
// }

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

void update_leds(uint8_t pos) {
    
    if (pos < 64)
        PORTB = 0b00000000;
    else if (pos < 128)
        PORTB = 0b00000001;
    else if (pos < 192)
        PORTB = 0b00000011;
    else if (pos < 254)
        PORTB = 0b00000111;
    else
        PORTB = 0b00010111;
}

int main() {
    
    init_rgb();
    ADC_init(); 
   // uart_init();
    init_leds();

    while (1) {
        uint8_t adc_value = ADC_read(PC0);
        _delay_ms(20);
        wheel(adc_value);
        update_leds(adc_value);
       // print_hex_value(adc_value);
        //uart_printstr("\r\n");
    }
    
    return 0;
}
