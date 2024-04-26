#include "main.h"


// calcul de regression lineaire
// https://calculis.net/droite-regression-lineaire
// #define TOS     272.38874895046
// #define k       0.94248530646516

void ADC_init() {
    
    // Set reference as 1.1V
    ADMUX = (1 << REFS1) | (1 << REFS0);
    
    // Enable ADC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);

}

uint16_t readTemperatureVoltage(void) {
    // Select ADC channel
    ADMUX |= (1 << MUX3);
    
    // Start ADC conversion
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    return ((ADCH << 8) | ADCL);
}

void    print_number(uint16_t x) {

    char base[10] = "0123456789";
    if (x >= 10)
        print_number(x / 10);
    uart_tx(base[x % 10]);

}

int convertVoltageToTemperature(uint16_t voltage) {
    return (int)(voltage * 25 / 314);
}

int main() {
    
    ADC_init(); 
    uart_init();

    while (1) {

        uint16_t voltage = readTemperatureVoltage();
        int temperature = convertVoltageToTemperature(voltage);
        _delay_ms(20);
        print_number(temperature);
        uart_printstr("\r\n");
    }
    
    return 0;
}
