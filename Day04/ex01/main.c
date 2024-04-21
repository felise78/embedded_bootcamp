#include "main.h"

volatile uint8_t 		ack = 0;

void i2c_read(void) { 
  
    TWCR = (1 << TWINT) | (1 << TWEN);      // Continue reading
    TWCR |= (ack << TWEA);                  // TWEA to 1 enable the ack / 0 for nack
    while (!(TWCR & (1 << TWINT)));         // Wait for transmission to complete
        
}

void send_command()
{
    i2c_start();
        i2c_write(AHT20_ADDR << 1);
        uint8_t tab[] = {CMD_MSR, DATA0, DATA1};
        for (int i = 0; i < 3; ++i)
        {
            i2c_write(tab[i]);
            if (TW_STATUS != TW_MT_DATA_ACK)
                uart_error("error_write");
            
        }
    i2c_stop();
}

void read_values(){

    i2c_write((AHT20_ADDR << 1) | 0x01); // addr + Reading bit
    ack = 1;
    do {
        i2c_read();
        if (TW_STATUS != TW_MR_DATA_ACK)
            uart_error("error read");
    }
    while ((TWDR & (1<< 7)));
}

void print_values(){

    print_hex_value(TWDR);
    uart_tx(' ');
    for (int i = 0; i < 5; ++i) {
        ack = 1;
        i2c_read();
        if (TW_STATUS != TW_MR_DATA_ACK)
            uart_error("error read");
        print_hex_value(TWDR);
        uart_tx(' ');
    }
    ack = 0;
    i2c_read();
    if (TW_STATUS != TW_MR_DATA_NACK)
        uart_error("error read");
    print_hex_value(TWDR);
    uart_tx('\r');
    uart_tx('\n');
}

int main ()
{
    // init
    uart_init();
    i2c_init();
    
    // starting i2c communication
    i2c_start();
    _delay_ms(40);
    i2c_write(AHT20_ADDR << 1);

    if (!(TWDR & (1 << 3))) //p8 de l'autre doc AHT20 // si la calib est pas faite
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
    
    // loop to read and print values from the sensor
    while (1)
    {
        send_command();
        _delay_ms(100);
        
        i2c_start();
        read_values();
        print_values();
        i2c_stop();

        _delay_ms(200);
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