#include "main.h"

void ADC_init() {
    
    // Set AVCC as reference voltage
    ADMUX = (1 << REFS0);
    
    // Enable ADC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);

}

uint16_t ADC_read(uint16_t channel) {
    // Select ADC channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    
    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));
    
    uint16_t val = ADC; 

    return val;
}

void    print_number(uint16_t x) {
    char base[10] = "0123456789";
    if (x >= 10)
        print_number(x / 10);
    uart_tx(base[x % 10]);
}

int main() {
    
    ADC_init(); 
    uart_init();

    while (1) {
        uint16_t adc_POT = ADC_read(PC0);
        uint16_t adc_LDR = ADC_read(PC1);
        uint16_t adc_NTC = ADC_read(PC2);
        
        _delay_ms(20);
        print_number(adc_POT);
        uart_printstr(", ");
        print_number(adc_LDR);
        uart_printstr(", ");
        print_number(adc_NTC);
        uart_printstr("\r\n");
    }
    
    return 0;
}
