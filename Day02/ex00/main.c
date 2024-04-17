#include "main.h"

// p74. Interrupt vectors  

// Fonction d'interruption appelée lorsqu'un changement d'état est détecté sur SW1
ISR(INT0_vect) {

   _delay_ms(50);

    cli();
    
    PORTB ^= (1 << PORTB0);

    sei();
   
}

// EICRA (External Interrupt Control Register A) :
// Ce registre permet de configurer les modes de déclenchement des interruptions externes INT0 et INT1. Chaque paire de bits dans ce registre contrôle le mode de déclenchement pour une interruption externe spécifique.
//     Bits 1 et 0 : Contrôlent le mode de déclenchement de l'interruption externe INT0.
//     Bits 3 et 2 : Contrôlent le mode de déclenchement de l'interruption externe INT1.

// EIMSK (External Interrupt Mask Register) :
// Ce registre permet d'activer les interruptions externes INT0 et INT1 en les masquant ou en les activant.
//     Bit 0 : Permet d'activer ou de désactiver l'interruption externe INT0.
//     Bit 1 : Permet d'activer ou de désactiver l'interruption externe INT1.

int main() 
{
    // init de la LED
    DDRB |= (1 << PB0);
    PORTB |= (1 << PB0);

    // init du boutton
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    // p80. 
    // activer les vecteurs d'interruptions 
    EICRA |= (1 << ISC00);
    EICRA |= (1 << ISC01);

    EIMSK |= (1 << INT0);

    sei();

    while (1);
}

