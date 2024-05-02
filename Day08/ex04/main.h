#ifndef MAIN_H
# define MAIN_H

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include <stdbool.h>
	#include <stdlib.h>

	#define MAX 			13 // #FULLRAINBOW + '\r'
	#define LED_OFF     	0xFF000000
	// #define LED_ON      	0xFFFFFFFF
	
	// spi.c
	#define SPI_SS      PB2
	#define SPI_MOSI    PB3
	#define SPI_MISO    PB4
	#define SPI_SCK     PB5
	void SPI_init(void);
	void SPI_MasterTransmit(char data);
	void spi_send_32(uint32_t data);
	void SPI_set_LEDS(uint32_t led1, uint32_t led2, uint32_t led3);


	// uart.c
	#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
	void uart_init();
	void uart_tx(char data);
	char uart_rx(void);
	void uart_printstr(const char *str);

	// parsing.c
	bool strcmp_cheatcode(char *str);
	bool parse(char *color);

	// utils.c
	void    print_number(uint32_t x);
	uint8_t charToHex(char value);
	uint8_t hexToDec(char hex1, char hex2);

#endif