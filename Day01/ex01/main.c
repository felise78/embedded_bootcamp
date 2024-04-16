#include "main.h"

int main() 
{
	// Timer 1 - 16 bits
	// Mode 14. PWM : Pulse Width Managment

	DDRB |= (1 << DDB1);

	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10);

	ICR1 = F_CPU / 1024;
	OCR1A = ICR1 / 2;

	while (1)
	{
		;
	}
}