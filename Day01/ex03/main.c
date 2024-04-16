#include "main.h"

int main() 
{
	DDRB |= (1 << DDB1);

	TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13);
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12);
    TCCR1B |= (1 << CS10);

	ICR1 = F_CPU / 1024;    // 15625
    int gap = ICR1 / 10;    // 1562
    OCR1A = gap;

	while (1)
	{
        if (!(PIND & (1 << SW1_PIN))) { // Si SW1 est enfoncé // incremente de 10 %
            _delay_ms(10); 
            if (!(PIND & (1 << SW1_PIN))) {
                if (OCR1A < ICR1)
					OCR1A += gap;
                while (!(PIND & (1 << SW1_PIN)));
            }
        }

        if (!(PIND & (1 << SW2_PIN))) { // Si SW2 est enfoncé // decremente de 10 %
            _delay_ms(10);
            if (!(PIND & (1 << SW2_PIN))) { 
                if (OCR1A > gap)
					OCR1A -= gap;
                while (!(PIND & (1 << SW2_PIN)));
            }
        }
    }
    return 0;
}