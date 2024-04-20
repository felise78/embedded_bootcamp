#include "main.h"

void i2c_init() {

    TWSR = 0;                   // Réglage de prescaler à 1
    TWBR = (uint8_t)TWBR_VAL;   // Réglage de la valeur du bit rate register
}

void i2c_start()
{
    //p.225
    TWCR = (1 << TWEN);
    TWCR |= (1 << TWSTA);
	TWCR |= (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

    // p.225 : Load SLA_W into TWDR Register. Clear TWINT bit in TWCR to start 
    // transmission of address
    // TWDR = SLA_W;
    // TWCR = (1<<TWINT) | (1<<TWEN);
}

void i2c_stop() {

    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
  //  while (TWCR & (1 << TWSTO));
}

void i2c_write(unsigned char data) {

    TWDR = data;                        // Load data into data register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Clear TWINT bit in TWCR to start transmission of data
    while (!(TWCR & (1 << TWINT)));     // Wait for transmission to complete
}

void i2c_read(void) {
   // unsigned char temp_data[6];
    
  //  for (int i = 0; i < 5; ++i) {
   //     temp_data[i] = TWDR;                // Read temperature data
       // print_hex_value(TWDR);
        TWCR = (1 << TWINT) | (1 << TWEN);  // Continue reading
        TWCR |= (1 << TWEA);                 // TWEA to 1 enable the ack
        while (!(TWCR & (1 << TWINT)));     // Wait for transmission to complete
   // }
   // temp_data[5] = TWDR;                    // Read last byte
        
}

int main ()
{
    uart_init();
    i2c_init();

    i2c_start();
    _delay_ms(40);
    
    // p227 :  load SLA+W ??


    i2c_write(AHT20_ADDR << 1);
    
    i2c_write(0x71);
    i2c_stop();
    i2c_start();
    i2c_write((AHT20_ADDR << 1) | 0x01);
    i2c_read();

 
    if (!(TWDR & (1 << 3))) //p8 de l'autre doc // si la calib est pas faite
    {
        i2c_stop();
        i2c_start();
        i2c_write(AHT20_ADDR << 1);
        i2c_write(0xbe);
        i2c_write(0x08);
        i2c_write(0x00);
        _delay_ms(10);
    }
    i2c_stop();
    while (1)
    {
        i2c_start();

        i2c_write(AHT20_ADDR << 1);
        i2c_write(CMD_MSR);
        i2c_write(DATA0);
        i2c_write(DATA1);

        i2c_stop();
        _delay_ms(100);
        i2c_start();

        i2c_write((AHT20_ADDR << 1) | 0x01); // addr + reading bit
        
        i2c_read();
        print_hex_value(TWDR);
        uart_tx(' ');
        if (!(TWDR & (1<< 7)))
        {
            for (int i = 0; i < 6; ++i) {
                i2c_read();
                print_hex_value(TWDR);
                uart_tx(' ');
            } 
        }
        uart_tx('\r');
        uart_tx('\n');

        i2c_stop();
        _delay_ms(1000);
    }
}

// p232.
// TWEN must be written to one to enable the TWI. The TWEA bit must be written to one to enable the
// acknowledgement of the device’s own slave address or the general call address. TWSTA and TWSTO must be
// written to zero.

// p13 de la doc AHT20 : 
// The sensor needs time to collect. After the host sends
// a measurement command (0xAC), delay more than 80 milliseconds 
// before reading the converted data and judging whether 
// the returned status bit is normal.