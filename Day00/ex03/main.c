#include "main.h"


int main(void) {

    // Configure la broche PD2 (SW1) en tant qu'entrée
    DDRD &= ~(1 << BUTTON_PIN);
    PORTD |= (1 << BUTTON_PIN);

    // Configure la broche PB0 (D1) en tant que sortie
    DDRB |= (1 << LED_PIN);

    // Variables pour stocker les états du bouton
    uint8_t prev_button_state = 0;
    uint8_t current_button_state = 0;

    while (1) {
        // Enregistre l'état actuel du bouton
        current_button_state = PIND & (1 << BUTTON_PIN);

        // Attendre un court laps de temps pour eviter les rebonds
        _delay_ms(10);

        // Vérifier si le bouton est passé de l'état relâché à l'état appuyé
        if (prev_button_state && !current_button_state) {
            // Inverser l'état de la LED PB0
            PORTB ^= (1 << LED_PIN);
        }

        // Mettre à jour l'état précédent du bouton
        prev_button_state = current_button_state;
    }

    return 0;
}

/* LES EFFETS REBONDS */

// Les "effets rebonds" sont un phénomène courant lors de l'utilisation de 
// boutons physiques. Ces effets rebonds peuvent entraîner plusieurs interruptions indésirables 
// lorsqu'un bouton est pressé ou relâché, ce qui peut perturber le comportement attendu de 
// votre programme.

// Pour gérer les effets rebonds, vous pouvez mettre en œuvre une technique de débouncing. 
// Une façon simple de le faire est d'ajouter une petite temporisation après la détection d'un 
// changement d'état du bouton, et de ne réagir qu'après avoir attendu un laps de temps fixe
// pour permettre aux rebonds de se dissiper.