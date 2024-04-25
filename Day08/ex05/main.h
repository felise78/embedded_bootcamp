#ifndef MAIN_H
# define MAIN_H

	#include <avr/io.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>

	void ADC_init();
	uint8_t ADC_read(uint8_t channel);

#endif