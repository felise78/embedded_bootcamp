#include "main.h"

int main(void) {

    // Configuration du port PB1 (D2) comme sortie
    DDRB |= (1 << DDB1);

    volatile uint32_t time_counter = 0;

    // calcul du nombre d'iterations necessaires pour arriver a 0.5 secondes :  
    // 
    // 0.5 x F_CPU = 8 000 000
    // 8 000 000 / 3 = 266667

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

// maybe try without a if 
// while ( i < 100000UL )