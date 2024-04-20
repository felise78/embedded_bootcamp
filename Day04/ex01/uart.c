#include "main.h"

void uart_init() {
    // Set baud rate
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    // Enable transmitter
    UCSR0B = (1 << TXEN0);
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_printstr(const char *str)
{
    while (*str)
    {
        uart_tx(*str++);
    }
}