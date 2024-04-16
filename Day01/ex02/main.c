#include "main.h"

int main() 
{
	// Timer 1 - 16 bits
	// Mode 14. PWM : Pulse Width Managment

	DDRB |= (1 << DDB1);

	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10);

    // Calculating the values for 1Hz frequency and 10% duty cycle
    // Frequency = F_CPU / (N * (1 + TOP)), where N is the prescaler and TOP is ICR1
    // 1Hz = F_CPU / (1024 * (1 + ICR1))
    // ICR1 = F_CPU / (1Hz * 1024) - 1
    // Duty cycle = OCR1A / ICR1
    // 10% = OCR1A / ICR1
    // OCR1A = 0.1 * ICR1

	ICR1 = F_CPU / 1024;
	OCR1A = ICR1 / 10;


	while (1)
		;
}