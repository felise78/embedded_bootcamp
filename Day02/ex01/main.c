#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t duty_cycle = 0; // Valeur du rapport cyclique PWM // pwm value

#define PWM_FREQUENCY 1000
#define OCR1A_VALUE (F_CPU / (1024UL * PWM_FREQUENCY) - 1)

// void init_timer0() {

//     // Configuration du Timer0 pour générer une interruption toutes les 1 ms
//     TCCR0A |= (1 << WGM01);    // Mode de comptage CTC
//     OCR0A = 249;                // Valeur de comparaison pour obtenir une interruption toutes les 1 ms
//     TIMSK0 |= (1 << OCIE0A);   // Activation de l'interruption sur comparaison
//     TCCR0B |= (1 << CS01) | (1 << CS00); // Configuration du prescaler à 64

// }

// void init_timer1() {

//     // Configuration du Timer1 pour la génération du PWM
//     TCCR1A = 0; // Aucune action sur les broches OC1A et OC1B (mode normal)
//     TCCR1B = (1 << WGM12); // Mode CTC, le timer s'arrête lorsqu'il atteint la valeur OCR1A

//     // Charger la valeur de comparaison OCR1A
//     OCR1A = OCR1A_VALUE;
//     TCCR1B |= (1 << CS12) | (1 << CS10);
// }

// void init_timer0() {
//     // Configuration du Timer0 pour une interruption périodique toutes les 1 ms
//     TCCR0A |= (1 << WGM01); // Mode CTC (Clear Timer on Compare Match)
//     OCR0A = 12; 
//     //  OCR0A = 249; // Valeur de comparaison pour obtenir une fréquence de 1 kHz
//     TIMSK0 |= (1 << OCIE0A); // Activation de l'interruption sur comparaison A
//     TCCR0B |= (1 << CS01) | (1 << CS00); // Préscaleur 64
// }

// // Fonction d'initialisation du Timer1
// void init_timer1() {
//     // Configuration du Timer1 pour générer un signal PWM
//     TCCR1A |= (1 << COM1A1) | (1 << WGM10); // Mode PWM, Clear OC1A on Compare Match
//     TCCR1B |= (1 << WGM12) | (1 << CS11); // Mode PWM, Préscaleur 8
//     DDRB |= (1 << PB1); // Définir PB1 (broche 9) comme sortie
// }

// // Fonction d'interruption du Timer0
// ISR(TIMER0_COMPA_vect) {
//     // Incrémentation du rapport cyclique de la LED
//     duty_cycle += 10;
//     if (duty_cycle > 100) {
//         duty_cycle = 0; // Réinitialisation du rapport cyclique si supérieur à 100 %
//     }
//     OCR1A = (duty_cycle * 255) / 100; // Mise à jour du registre de comparaison du Timer1
// }


ISR (TIMER1_OVF_vect) {
    PORTB ^= (1 << PORTB1); // Toggle the 5th data register of PORTB
    TCNT1 = 64755; // 50 ms for 16MHz clock
}


int main() {

    DDRB = (1 << DDB1); // Set 5th data direction register of PORTB. A set value means output
    TCNT1 = 64755; // 50 ms for 16MHz clock
    TCCR1A = 0x00; // Set normal counter mode
    TCCR1B = (1<<CS10) | (1<<CS12); // Set 1024 pre-scaler
    TIMSK1 = (1 << TOIE1); // Set overflow interrupt enable bit

    sei();

    while (1) {
        _delay_ms(1000);
    }

    return 0;
}