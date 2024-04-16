#include "main.h"

int main() 
{
	uint16_t cycle = 10;

	DDRB |= (1 << DDB1);

	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10);

	ICR1 = F_CPU / 1024;

	while (1)
	{
        if (!(PIND & (1 << SW1_PIN))) { // Si SW1 est enfoncé // incremente de 10 %
            _delay_ms(10); 
            if (!(PIND & (1 << SW1_PIN))) {
                if (cycle <= 10)
				{
					cycle--;
					OCR1A = ICR1 / cycle;
				}
                while (!(PIND & (1 << SW1_PIN))); // Attendre que le bouton soit relâché
            }
        }

        if (!(PIND & (1 << SW2_PIN))) { // Si SW2 est enfoncé // decremente de 10 %
            _delay_ms(10);
            if (!(PIND & (1 << SW2_PIN))) { 
                if (cycle >= 1)
				{
					cycle++;
					OCR1A = ICR1 / cycle;
				}
                while (!(PIND & (1 << SW2_PIN))); // Attendre que le bouton soit relâché
            }
        }
    }
    return 0;
}