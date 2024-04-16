#include "main.h"

int main(void) {

    // Configuration du port PB1 (D2) comme sortie
    DDRB |= (1 << DDB1);

    volatile uint32_t time_counter = 0;

    // calcul du nombre d'iterations :  
    // 
    // 0.5 x 16 000 000
    // = 8 000 000 / 3 = 266667

    while (1) {

        if (time_counter >= 266667) { 
            // Bascule de l'état de la LED D2 (PB1)
            PORTB ^= (1 << PB1);
            
            time_counter = 0;
        }
        time_counter++;
    }

    return 0;
}