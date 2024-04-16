#include "main.h"

// Configurer le port B (où se trouve le PB0) en tant que sortie en définissant le bit 
// correspondant du registre DDRB.
// Mettre le bit correspondant du registre PORTB à 1 pour allumer la LED.

// Vous devez à chaque fois expliquer la fonction et les valeurs
// assignées aux registres en commentaire !

// p88 du Data Sheet
int main ()
{
	// Configurer la broche PB0 (D1) en tant que sortie (1) / HIGH
    DDRB |= (1 << PB0);

    // Allumer la LED D1 (PB0)
    PORTB |= (1 << PB0);

    while (1) {
    }
    
    return 0;
}
