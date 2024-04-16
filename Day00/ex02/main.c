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

// Dans cet exemple, nous utilisons les registres DDRD, PORTD pour configurer la broche 
// PD2 (SW1) comme une entrée avec la résistance de tirage activée, et nous utilisons le 
// registre PIND pour lire l'état du bouton.

// Ensuite, nous utilisons les registres DDRB, PORTB pour configurer la broche PB0 (D1) 
// comme une sortie, et nous contrôlons son état en fonction de l'état du bouton LU du registre PIN.

// Ce code est conçu pour boucler indéfiniment, vérifiant constamment l'état du bouton 
// et mettant à jour l'état de la LED en conséquence.
