#include "main.h"

void uart_init() {

    // p181.
    // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)(UBRR_VALUE);
    // Set frame format: 8 data, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Enable transmitter
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0) | (1 << TXEN0);
}

void uart_tx(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

char uart_rx(void) {

    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void uart_printstr(const char *str)
{
    while (*str)
    {
        uart_tx(*str++);
    }
}