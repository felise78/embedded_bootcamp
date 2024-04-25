#include "main.h"

void ADC_init() {
    
    // Set REFS1:0 bits to select AVCC as reference voltage
    // ADLAR : mettre le bit a 1 pour avoir le resultat sur 8bits 
    ADMUX = (1 << REFS0)| (1 << ADLAR);
    
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

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

void print_hex_value(unsigned char titouan) {

	static char buffer[3] = { '0', '0', '\0'};
    int i =  sizeof(buffer) - 1;
	for (int j = 0; j < 2; j++) {
        buffer[--i] = "0123456789ABCDEF"[titouan & 0x0f];
        titouan >>= 4;
    }
	uart_printstr(buffer);
}

int main() {
    
    ADC_init(); 
    uart_init();

    while (1) {
        uint8_t adc_pote = ADC_read(PC0);
        uint8_t adc_LDR = ADC_read(PC1);
        uint8_t adc_NTC = ADC_read(PC2);
        _delay_ms(20);
        print_hex_value(adc_pote);
        uart_printstr(", ");
        print_hex_value(adc_LDR);
        uart_printstr(", ");
        print_hex_value(adc_NTC);
        uart_printstr("\r\n");
    }
    
    return 0;
}
