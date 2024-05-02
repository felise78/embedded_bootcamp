#include "main.h"

#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182

void uart_init() {

    // p181.

    // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)(UBRR_VALUE);

    // Set frame format: 8 data, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void uart_tx(char c) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = c;
}

int main() {

    uart_init();
    while (1) {
        uart_tx('Z');
        uart_tx('\r');
        uart_tx('\n');
        _delay_ms(1000);
    }
}

// 

// "L'UART du MCU doit être configuré en 115200 8N1" 

// doit être configuré pour une communication série à une 
// vitesse de 115200 bauds, avec une configuration de 8 bits 
// de données, pas de parité (N = None), et 1 bit d'arrêt.

// 115200 bauds : C'est la vitesse de transmission des 
// données en bauds. Cela signifie que 115200 symboles 
// (ou bits) sont transmis par seconde.

// 8 bits de données : Chaque caractère envoyé ou reçu sera 
// composé de 8 bits de données. Ces bits représentent les 
// informations utiles à transmettre, comme des lettres, des 
// chiffres ou d'autres données.

// N1 : Cela signifie qu'il n'y a pas de bit de parité. 
// Le bit de parité est un bit supplémentaire utilisé pour 
// la détection d'erreurs. Dans ce cas, il est spécifié qu'il 
// n'y a pas de parité (None).

// 1 bit d'arrêt : Après les 8 bits de données, il y a un bit 
// d'arrêt qui indique la fin de la transmission d'un caractère. 
// Cela permet au récepteur de savoir quand commence et se termine 
// chaque caractère.

// ------------------------------------------------ //

// UBRRnL doit être calculé en fonction de UART_BAUDRATE et F_CPU :

// Le registre de débit en bauds USART (Universal Synchronous 
// Asynchronous Receiver Transmitter), souvent abrégé en UBRR, 
// est un registre utilisé dans les microcontrôleurs et les 
// microprocesseurs pour définir la vitesse de transmission des
// données sur une liaison série.
// La liaison série est un moyen de communication où les données
// sont envoyées en série, c'est-à-dire une à la fois, sur un 
// seul fil.
// Le débit en bauds est une mesure de la vitesse à laquelle les
// données sont transmises sur la liaison série et est mesuré en
// bauds. Un baud représente un symbole par seconde. 
// Par exemple, à un débit en bauds de 9600, cela signifie que 
// 9600 symboles (ou bits) sont envoyés par seconde.
// Le registre UBRR permet de configurer la vitesse de 
// transmission des données en définissant une valeur numérique 
// qui correspond à une fréquence de transmission spécifique. 
// Cette valeur est calculée en fonction de la fréquence 
// d'horloge du microcontrôleur ou du microprocesseur ainsi que 
// de la vitesse de transmission souhaitée.
// En réglant correctement le contenu du registre UBRR, 
// on assure que le périphérique de communication série 
// fonctionne à la même vitesse que le périphérique avec 
// lequel il communique, évitant ainsi les erreurs de 
// synchronisation et garantissant une transmission fiable des 
// données.

