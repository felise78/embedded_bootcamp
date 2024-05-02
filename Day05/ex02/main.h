#ifndef MAIN_H
# define MAIN_H

	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdbool.h>
	#include <stddef.h>
	#include <avr/eeprom.h>

	#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
	
	void uart_init();
	void uart_printstr(const char *str);

#endif