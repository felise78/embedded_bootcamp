#include "main.h"

#define SW1_PIN 2
#define LED4_PIN 4
 // Exemple : adresse de début de la mémoire EEPROM
// 1024 octets de memoire EEPROM

volatile uint8_t compteur = 0;

// void EEPROM_write(uint8_t* addr, uint8_t value) {
//     eeprom_busy_wait();
//     eeprom_write_byte(addr, value);
// }

// uint8_t EEPROM_read(uint8_t* addr) {
//     eeprom_busy_wait();
//     return eeprom_read_byte(addr);
// }

void updateLEDs() {
    
    PORTB = (compteur & 0b00000111); // Utilise les 3 bits de poids faible de 'value' pour les LEDs D1, D2 et D3
   // Allumer la LED D4
    if (compteur >= 8) {
        PORTB |= (1 << LED4_PIN);
    } else {
        // Éteindre la LED D4
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
	// verifier si ya pas magic number
		// si ya pas
			//mettre a 0
			// mettre magic number
			
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




// // Command Byte Bit Coding p296
// #define CHIP_ERASE 	0b10000000 // use this one at the beginning
// // #define WR_FUSE_B	0b01000000
// // #define WR_LOCK_B	0b00100000
// // #define WR_FLASH	0b00010000
// // #define WR_EEPROM	0b00010001
// // #define R_SIGN_CAL	0b00001000
// // #define R_FUSE_LOCK	0b00000100
// // #define R_FLASH		0b00000010
// // #define R_EEPROM	0b00000011




// void configure_pins() {
//     // Définir les broches de contrôle comme sorties
//     DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
// }


// void send_command(uint8_t command) {
//     // Activer le chargement de commande (étape 1)
//     PORTD = (1 << PD1);

//     PORTD = command;

//     // Impulsion positive sur XTAL1
//     PORTD |= (1 << PD2);
   
//     // Impulsion négative sur WR
//     PORTD &= ~(1 << PD3);

//     // Attendre que RDY/BSY passe à l'état haut (étape 6)
//     while (!(PIND & (1 << PD0))) {
//     }
// }

// int main() {
    
//     configure_pins();
//     send_command(CHIP_ERASE);
    
//     while (1);

//     return 0;
// }

// int main() {
//     // Déclaration de la variable à écrire dans l'EEPROM
//     uint8_t data_to_write = 42;
//     // Écriture de la donnée dans l'EEPROM
//     eeprom_write_byte((uint8_t*)EEPROM_ADDRESS, data_to_write);
    
//     // Lecture de la donnée depuis l'EEPROM
//     uint8_t data_read = eeprom_read_byte((uint8_t*)EEPROM_ADDRESS);

//     // Vérification de la valeur lue depuis l'EEPROM
//     if (data_read == data_to_write) {
//         // La lecture et l'écriture sont réussies
//     } else {
//         // Il y a eu une erreur lors de la lecture ou de l'écriture
//     }

//     while(1) {
//         // Boucle infinie
//     }

//     return 0;
// }

// p 289 / MEMORY PROGRAMMING
// 6 lock bits : 1 : unprogrammed 
// 0 : programmed 
// The Lock bits can only be erased to “1” with the Chip Erase command
// p290. table 28-3. Lock bit protection modes
// p294. Table 28-12. 
// ATmega328P : 1Kbytes Size / Page size : 4 bytes / PCWORD : EEA[1:0]
// no of pages : 256 / pc page : EEA[9:2] // EEAMSB : 9

// p297 CHIP ERASE
// the chip erase will erase the Flash and EEPROM memories, plus lock bits.
// the lock bits are not reset until the program memory has been completely erased. 
// the Fuse bits are not changed (Fuse bits == Lock Bit Protection Modes // p289)

// ----------------------

// p295 : Figure 28-1 // Table 28-13
// Load Command “Chip Erase”
// Note: The EEPRPOM memory is preserved during Chip Erase if the EESAVE Fuse is programmed.
// 1.Set XA1, XA0 to “1" and "0”. This enables command loading.
// 2.Set BS1 to “0”.
// 3.Set DATA to “1000 0000”. This is the command for Chip Erase.
// 4.Give XTAL1 a positive pulse. This loads the command.
// 5.Give WR a negative pulse. This starts the Chip Erase. RDY/BSY goes low.
// 6.Wait until RDY/BSY goes high before loading a new command


// 299 - Programming the EEPROM