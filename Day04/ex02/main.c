#include "main.h"

volatile uint8_t 		ack = 0;

unsigned char           bytes[5] = {0};

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
            uart_error("error_write in send command");
        
    }
    i2c_stop();
    _delay_ms(100);
}

void read_values() {

    i2c_start();
    i2c_write((AHT20_ADDR << 1) | 0x01); // addr + Reading bit
    ack = 1;
    do {
        i2c_read();
        if (TW_STATUS != TW_MR_DATA_ACK)
            uart_error("error read");
    }
    while ((TWDR & (1 << 7)));   // p241 du Datasheet
    for (int i = 0; i < 5; ++i)
    {
        i2c_read();
        if (TW_STATUS != TW_MR_DATA_ACK)
            uart_error("error read");
        bytes[i] = TWDR;
    }
    ack = 0;
    i2c_read();
    if (TW_STATUS != TW_MR_DATA_NACK)
        uart_error("error read");
    i2c_stop();
    // for (int i = 0; i < 5; ++i)
    // {
    //     print_hex_value(bytes[i]);
    //     uart_tx(' ');
    // }
    // uart_tx('\r');
    // uart_tx('\n');
    
}

void convert_and_print_values(float *hum, float *temp) {

    *hum = 0;
    *temp = 0;
    char str[20];
   
    // loop for accuracy
    for (int i = 0; i < 3; i++) {
        
        send_command();
        read_values();
        // calculate humidity
        const uint32_t h0 = bytes[0];
        const uint32_t h1 = bytes[1];
        const uint32_t h2 = (bytes[2] & 0xF0) >> 4;
        const uint32_t h = (h0 << 12) | ( h1 << 4 ) | h2 ;
        // h <<= 12;
        // h += bytes[1];
        // h <<= 4;
        // h += bytes[2] >> 4;
        *hum += (float)(h / 1048576.0) * 100;
        dtostrf(*hum, 0, 1, str);
        uart_printstr(str);
        uart_printstr("\r\n");
        uint32_t t = 0;
        // calculate temperature
        t = bytes[2] & 0x0f;
        t <<= 8;
        t += bytes[3];
        t <<= 8;
        t += bytes[4];
        *temp += (float)(t / 1048576.0) * 200.0 - 50.0;
        dtostrf(*temp, 0, 1, str);
        uart_printstr(str);
        uart_printstr("\r\n");
        _delay_ms(50);
    }
    *hum /= 3;
    *temp /= 3;
}

void aht20_init()
{
    // starting i2c communication
    i2c_start();
    _delay_ms(40);
    i2c_write(AHT20_ADDR << 1);

    if (!(TWDR & (1 << 3))) // si la calib est pas faite
    {
        //uart_printstr("calibration\r\n");
        //i2c_stop();
        //i2c_start();
        i2c_write(AHT20_ADDR << 1);
        uint8_t tab[] = {0xbe, 0x08, 0x00};
        for (int i = 0; i < 3; ++i)
        {
            i2c_write(tab[i]);
            if (TW_STATUS != TW_MT_DATA_ACK)
                uart_error("error_write in send command");
            
        }
        _delay_ms(40);
    }
    else
        uart_success("success init");
    i2c_stop();
}

int main ()
{
    // init
    uart_init();
    i2c_init();
    aht20_init();
    
   // i2c_start();

    float hum = 0.0f;
    float temp = 0.0f;
    char str[20];
   // while (1)
   // {
        //send_command();
        //i2c_start();
        convert_and_print_values(&hum, &temp);
       // i2c_stop();
        uart_printstr("Temperature: ");
        dtostrf(temp, 0, 1, str);
        uart_printstr(str);
        uart_printstr("°C, ");
        uart_printstr("Humidity: ");
        dtostrf(hum, 0, 1, str);
        uart_printstr(str);
        uart_tx('%');
        uart_tx('\r');
        uart_tx('\n');
        _delay_ms(200);
   // }
}