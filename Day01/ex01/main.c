#include "main.h"

int main() 
{
	// Timer 1 - 16 bits
	// Mode 14. PWM : Pulse Width Managment

	DDRB |= (1 << DDB1);

	// je set le mode 14 : 
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13);
	TCCR1B |= (1 << WGM12);

	// pre-division a 1024
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);

	// comportement de la broche, ici mode non-inverse
	// OC1A = 0 lors de la detection d'egalite
	// OC1A = 1 lorsque le compteur passe a 0 (BOTTOM)
	TCCR1A |= (1 << COM1A1);

	ICR1 = F_CPU / 1024;
	OCR1A = ICR1 / 2;

	while (1)
		;
}