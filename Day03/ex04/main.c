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

void uart_printstr(const char* str)
{
    while (*str) {
        uart_tx(*str++);
    }
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int main() {

    uart_init();
    
    char recieved;
    char *user = "felise78";
    char *password = "motdepasse123";
    char *get_username = 0;
    char *get_password = 0;

    uart_printstr("username:");
    uint8_t i = 0;
    recieved = uart_rx();
    while (i < 8 && recieved == user[i])
    {
        i++;
        recieved = uart_rx();
    }
    if (i == 8)
        uart_printstr("\r\nvalid username");
    else
        uart_printstr("\r\ninvalid username");
    
    
    while (1);

    return 0;
}
