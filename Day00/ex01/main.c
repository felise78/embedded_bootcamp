#include "main.h"

int main ()
{
	// Configure le port B du registre DDRB où se trouve la broche PB0
    // ( a laquelle est connectee la LED D1 ) en tant que sortie (1) en definissant le bit a 1.
    DDRB |= (1 << PB0);

    // Allume la LED D1 en mettant le bit de la broche PB0 a 1 dans le registre PORTB
    // pour faire passer la broche en niveau logique HIGH (1) / (mise sous tension)
    PORTB |= (1 << PB0);

    while (1) {
    }
    
    return 0;
}
