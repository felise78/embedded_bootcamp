#include "main.h"

#define F_SCL 100000UL  // Fréquence de communication I2C (100 kHz)
#define TWBR_VAL 72 // ((F_CPU / F_SCL) - 16) / 2
#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182

void i2c_init() {

    TWSR = 0;  // Réglage de prescaler à 1
    TWBR = (uint8_t)TWBR_VAL;  // Réglage de la valeur du bit rate register 
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

void i2c_start()
{
    // p225 : send start condition : 
    // TWEN must be set to enable the 2-wire Serial Interface
    TWCR |= (1 << TWEN);
    // TWSTA must be written to one to transmit a START condition
    TWCR |= (1 << TWSTA);
    // TWINT must be written to one to clear the TWINT Flag
	TWCR |= (1 << TWINT);
    
    // p225
    // Wait for TWINT Flag set. This indicates that the START
    // condition has been transmitted
	while (!(TWCR & (1 << TWINT)));
	
    if ((TWSR & 0xF8) != 0x08)
    {
        uart_printstr("Error\n");
    }

	return;
}

void i2c_stop() {
    // Envoi de la condition d'arrêt (STOP)
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);

    // Attente de fin de transmission du STOP
    while (TWCR & (1 << TWSTO));
}

void uart_init() {
    // Set baud rate
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    // Enable transmitter
    UCSR0B = (1 << TXEN0);
    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void    print_number(uint8_t x)
{
    char base[10] = "0123456789";
    if (x >= 10)
        print_number(x / 10);
    uart_tx(base[x % 10]);
}


int main ()
{
    uart_init();
    i2c_init();
    i2c_start();
    print_number(TWSR);
    i2c_stop();
}