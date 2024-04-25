#ifndef MAIN_H
# define MAIN_H

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>
	#include <stdbool.h>
	#include <stdlib.h>

	#define UBRR_VALUE      ((F_CPU / (16 * BAUDRATE))) // p.182
	#define MAX 			13 // #FULLRAINBOW + '\r'

	void uart_init();
	void uart_tx(char data);
	char uart_rx(void);
	void uart_printstr(const char *str);

#endif