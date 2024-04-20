#ifndef MAIN_H
 #define MAIN_H

	#include <avr/io.h>
	#include <util/twi.h>

	// La bibliothèque util/twi.h est une bibliothèque standard 
	// en langage C qui fournit des fonctions pour utiliser le 
	// protocole de communication I2C (Inter-Integrated Circuit).
	// twi : two wire interface
	// qui est une autre appellation pour le protocole I2C.
	// Cette bibliothèque est souvent utilisée dans les 
	// microcontrôleurs AVR. Elle permet de faciliter la 
	// communication avec des périphériques externes, tels 
	// que des capteurs, des afficheurs, des modules de 
	// communication, etc., qui utilisent le protocole I2C.

#endif

// configurer l'I2C afin que la fréquence de communication 
// soit de 100 kHz :

// Dans le protocole I2C, la communication est basée sur 
// des signaux d'horloge et de données. La fréquence de 
// communication, mesurée en kilohertz (kHz), détermine 
// à quelle vitesse les données peuvent être transférées 
// entre les périphériques connectés au bus I2C. Dans ce 
// cas, une fréquence de 100 kHz signifie que les données 
// seront transmises à une vitesse de 100 000 bits par 
// seconde.