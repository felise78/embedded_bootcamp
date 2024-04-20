#ifndef MAIN_H
 #define MAIN_H

	#include <avr/io.h>
	#include <util/delay.h>
	#include <util/twi.h>

	#define F_SCL           100000UL  // Fréquence de communication I2C (100 kHz)
	#define TWBR_VAL        72 // ((F_CPU / F_SCL) - 16) / 2
	#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
	
	// datasheet AHT20 p13
	#define AHT20_ADDR      0x38 	
	#define CMD_MSR 		0b10101100
	#define DATA0   		0b00110011 
	#define DATA1   		0b00000000

	void	uart_init();
	void    print_number(uint8_t x);
	void	print_hex_value(char c);
	void	uart_tx(char data);
	void	uart_printstr(const char *str);

#endif