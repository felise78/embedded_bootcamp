#include "main.h"

void ADC_init() {
    
    // Set REFS1:0 bits to select AVCC as reference voltage
    // ADLAR : mettre le bit a 1 pour avoir le resultat sur 8bits 
    ADMUX = (1 << REFS0)| (1 << ADLAR);
    
    // Configure ADC with 8-bit resolution
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); 

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