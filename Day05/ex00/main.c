#include "main.h"

#define SW1_PIN 2
#define LED4_PIN 4
 // Exemple : adresse de début de la mémoire EEPROM
// 1024 octets de memoire EEPROM

volatile uint8_t compteur = 0;

void updateLEDs() {
    
    PORTB = (compteur & 0b00000111); // LEDs D1, D2 et D3
   // Allumer D4
    if (compteur >= 8) {
        PORTB |= (1 << LED4_PIN);
    } else {
        // Éteindre D4
        PORTB &= ~(1 << LED4_PIN);
    }
}

int main () {

	DDRB |= 0b00010111;  // D1, D2, D3, D4 en sortie
	DDRD &= ~(1 << SW1_PIN);
    PORTD |= (1 << SW1_PIN);

	uint8_t *addr;
	addr = (uint8_t *)0x42;
	compteur = eeprom_read_byte(addr); 
			
	while(1) {
		updateLEDs();
		if (!(PIND & (1 << SW1_PIN))) { // Si le bouton est enfoncé
			_delay_ms(50); // Attendre un court instant pour éviter les rebonds
			if (!(PIND & (1 << SW1_PIN))) { // Vérifier à nouveau si le bouton est enfoncé
				compteur++; // Incrémenter le compteur
				if (compteur == 16) // Limiter le compteur à 4
					compteur = 0;
				eeprom_write_byte(addr, compteur);
				//EEPROM_write(EEPROM_ADDR, compteur); // Sauvegarder le compteur dans l'EEPROM
				//updateLEDs(compteur); // Mettre à jour l'état des LEDs
				_delay_ms(200); // Attendre un court instant pour éviter les rebonds
				while (!(PIND & (1 << SW1_PIN)));
			}
		}
	}
}