#ifndef MAIN_H
 #define MAIN_H

	// librairies
	#include <avr/io.h>
	#include <util/delay.h>
	#include <util/twi.h>

	// uart
	#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
	void	uart_init();
	void	uart_tx(char data);
	void	uart_printstr(const char *str);
	//void 	uart_success(const char* msg);
	void 	uart_error(const char* msg);

	// I2C
	#define F_SCL           100000UL  	// Fréquence de communication I2C (100 kHz)
	#define TWBR_VAL        72 			// ((F_CPU / F_SCL) - 16) / 2
	#define AHT20_ADDR      0x38 		// datasheet AHT20 p13 //
	#define CMD_MSR 		0b10101100	//                     //
	#define DATA0   		0b00110011 	//                     //
	#define DATA1   		0b00000000	/////////////////////////
	void 	i2c_init();
	void 	i2c_start();
	void	i2c_stop();
	void	i2c_write(unsigned char data);
	void	i2c_read(void);

	// utils 
	void    print_number(uint8_t x);
	void	print_hex_value(char c);

#endif