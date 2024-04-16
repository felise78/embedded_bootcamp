#ifndef MAIN_H
 #define MAIN_H

	#include <avr/io.h>

#endif


/* LES REGISTRES AVR */

// Les registres AVR jouent un rôle crucial dans le fonctionnement du microcontrôleur. 
// Ils sont utilisés pour stocker des données temporaires, des adresses mémoire, des paramètres 
// de configuration et d'autres informations nécessaires pour l'exécution du programme.

// DDRx : Ce registre est utilisé pour définir la direction des broches d'un port donné 
// comme entrée (0) ou sortie (1). "x" fait référence au numéro du port (A, B, C, etc.). 
// Par exemple, DDRB est le registre de direction pour le port B.

// PORTx : Ce registre est utilisé pour écrire des données sur les broches d'un port
// donné. Lorsqu'une broche est configurée comme sortie (définie à 1 dans le registre 
// DDRx correspondant), écrire un 1 dans le bit correspondant de PORTx fait passer la 
// broche à l'état haut (logique 1) et écrire un 0 la met à l'état bas (logique 0).

// PINx : Ce registre est utilisé pour lire l'état des broches d'un port donné. Lire le 
// registre PINx donne l'état actuel de toutes les broches configurées comme entrée 
// (définies à 0 dans le registre DDRx correspondant). Chaque bit dans le registre PINx 
// représente l'état de la broche correspondante.




/* BROCHE (I/O) Entree/Sortie  /  GPIO : "General Purpose Input/Output"  */

// Une broche d'entrée/sortie (I/O) en électronique est une interface par laquelle 
// un composant électronique, tel qu'un microcontrôleur, peut communiquer avec le monde 
// extérieur. Cette broche peut être configurée pour fonctionner soit en tant qu'entrée, 
// soit en tant que sortie, d'où le terme "entrée/sortie".

// Entrée : Lorsqu'une broche est configurée en tant qu'entrée, elle peut recevoir des 
// signaux ou des données provenant de l'extérieur. Par exemple, elle peut lire des données
// provenant de capteurs, de boutons ou d'autres périphériques électroniques. L'état de 
// l'entrée peut être lu par le composant électronique qui la contrôle, comme un 
// microcontrôleur.

// Sortie : Lorsqu'une broche est configurée en tant que sortie, elle peut envoyer des 
// signaux ou des données vers des dispositifs externes. Par exemple, elle peut envoyer 
// des signaux à des actionneurs tels que des moteurs, des LED ou d'autres composants pour 
// les contrôler.

// Les broches d'entrée/sortie sont fondamentales dans la conception de circuits 
// électroniques car elles permettent aux composants de communiquer et d'interagir avec le 
// monde extérieur. La capacité à contrôler et à lire des signaux provenant de divers 
// périphériques externes est cruciale dans de nombreux systèmes embarqués, comme les 
// robots, les appareils IoT et les systèmes de contrôle industriels.