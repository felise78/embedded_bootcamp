#include "main.h"

void i2c_init() {

    TWSR = 0;                   // Réglage de prescaler à 1
    TWBR = (uint8_t)TWBR_VAL;   // Réglage de la valeur du bit rate register
    TWCR = (1 << TWEN);
}

void i2c_start() {
    //p.225
    TWCR = 0;
    TWCR = (1 << TWEN);
    TWCR |= (1 << TWSTA);
	TWCR |= (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void i2c_stop() {

    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    while (TWCR & (1 << TWSTO))
    {
        ;
       //uart_error("stop\r\n");
    }
}

void i2c_write(unsigned char data) {

    TWDR = data;                        
    TWCR = (1 << TWINT) | (1 << TWEN);      // Clear TWINT bit in TWCR to start transmission of data
    while (!(TWCR & (1 << TWINT)))
    {
        ;
        // uart_error("write");
        // uart_tx(data);
    }         // Wait for transmission to complete
}

// i2c_read is in main.c