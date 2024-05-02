#include "main.h"

#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
#define PRESCALE 1024

void    init_timer0()
{
    // mode 7 (compte de 0 a OCRA) : p115
    TCCR0A |= (1 << WGM01) | (1 << WGM00); 
    TCCR0B |= (1 << WGM02);
    // pre-division de 1024 : p117
    TCCR0B |= (1 << CS02) | (1 << CS00);
    // ici OCRA est reglee sur 2 secondes
    OCR0A = (F_CPU / PRESCALE) / 100;
}

void    init_interrupt()
{
    TIMSK0 |= (1 << OCIE0A);
    sei();
}

void uart_init() {

    // p181.
    // Set baud rate
    UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
    UBRR0L = (unsigned char)(UBRR_VALUE);
    // Set frame format: 8 data, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    // Enable transmitter
    UCSR0B = (1 << TXEN0);
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

ISR (TIMER0_COMPA_vect) {

   uart_printstr("Hello World!\r\n");
   _delay_ms(2000);
   
}

int main() {

    init_timer0();
    init_interrupt();
    uart_init();
    
    while (1);
}
