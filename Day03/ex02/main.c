#include "main.h"


#define PRESCALE 1024

void uart_init() {

    // p181.
    // Set baud rate
    UBRR0 = (unsigned char)(UBRR_VALUE);
    // Set frame format: 8 data, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Enable transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

// recevoir
char uart_rx(void) {
    // Attendre la réception d'un caractère
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

// transmettre
void uart_tx(char data) {
    // Attendre que le tampon de transmission soit prêt
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

int main() {

    uart_init();

    char received_char;

    while (1) {
        received_char = uart_rx();
        uart_tx(received_char);
        _delay_ms(10);
    }

    return 0;
}
