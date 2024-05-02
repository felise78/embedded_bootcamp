#include "main.h"

#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182

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

ISR(USART_RX_vect) { // canal de réception USART
   
    char receivedByte = UDR0;
    
    if(receivedByte >= 'a' && receivedByte <= 'z') {
        receivedByte -= 32;
    } else if(receivedByte >= 'A' && receivedByte <= 'Z') {
        receivedByte += 32;
    }

    // Attendre jusqu'à ce que le tampon de transmission soit vide
    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = receivedByte;
}


int main() {

    uart_init();
    //active les interruptions
    sei();
    
    while (1);

    return 0;
}
