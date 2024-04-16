#include "main.h"

int main(void) {
    // Configurer la broche PD2 (SW1) en tant qu'entrée
    DDRD &= ~(1 << BUTTON_PIN);
    PORTD |= (1 << BUTTON_PIN);

    // Configurer la broche PB0 (D1) en tant que sortie
    DDRB |= (1 << LED_PIN);

    while (1) {
        // Lire l'état du bouton SW1 (PD2)
        if (!(PIND & (1 << BUTTON_PIN))) { // Si le bouton est enfoncé (PD2 est 0)
            // Allumer la LED D1 (PB0)
            PORTB |= (1 << LED_PIN);
        } else { // Si le bouton est relâché (PD2 est 1)
            // Éteindre la LED D1 (PB0)
            PORTB &= ~(1 << LED_PIN);
        }
    }

    return 0;
}

// Le registre PINX donne l'etat actuel de toutes les broches configurees 
// comme entrees (definie a 0 dans le registre DDRX correspondant)
