#include "main.h"

volatile uint8_t ascendant = 1;

#define LED_FREQ 50
#define PRESCALE1 256
const uint16_t ledfreq = F_CPU / (PRESCALE1 * LED_FREQ); 

#define PWM_FREQ 2
#define PRESCALE0 1024
const uint8_t pwm_freq =  (F_CPU / PRESCALE0) / 100 * PWM_FREQ;

volatile uint8_t width = 1;

ISR (TIMER0_COMPA_vect) {
    
    if (ascendant)
    {
        if (width == 100)
            ascendant = 0;
        width++;
    }
    else 
    { 
        if (width == 0)
            ascendant = 1;
        width--;
    }
    OCR1A = (ledfreq / 100) * width;
}

void    init_timer0()
{
   // mode 7 (compte de 0 a OCRA)
    TCCR0A |= (1 << WGM01) | (1 << WGM00); 
    TCCR0B |= (1 << WGM02);
    // pre-division de 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);
    OCR0A = pwm_freq;
}

void    init_timer1()
{
    TCCR1A = 0;
    TCCR1B = 0;

    // mode 14
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
    // pre-division de 256
    TCCR1B |= (1 << CS12);// | (1 << CS10);
    // comportement de sortie 
    TCCR1A |= (1 << COM1A1); // allume la led a bottom / 0 puis l'eteint a OCR1A

    ICR1 = ledfreq;
}

void    init_interrupt()
{
    TIMSK0 |= (1 << OCIE0A);
     sei();
}

int main() {


    DDRB |= (1 << PB1);
    init_timer0();
    init_timer1();
    init_interrupt();

   

    while (1);
}