#include "main.h"

#include <stdio.h>
#include <stdint.h>

#define EEPROM_SIZE 1024

// bool safe_eeprom_read(void *buffer, size_t offset, size_t length)


bool safe_eeprom_write(void *buffer, size_t offset, size_t length)
{
	(void)offset;

	// protections								  	   // taille du magic number
	if (buffer == NULL || length == 0 || offset + length + sizeof(uint16_t) > EEPROM_SIZE) {
        return false;
    }

	// init du pointeur pour recup la data
	uint8_t *buff = (uint8_t*)buffer;

	// concatenation de mon magic number 0xFE42 + mes datas dans un buffer temp
	uint8_t temp_buffer[length + sizeof(uint16_t)];
	temp_buffer[0] = 0xFE;
	temp_buffer[1] = 0x42;
	for (size_t i = 2; i < length + 2; i++)
	{
		temp_buffer[i + 2] = buff[i];
	}	

	// verifier que ce n'est pas deja ecrit dans l'eeprom
	size_t i = 0;
	for (; i < length + 2; i++)
	{
		uint8_t tmp = eeprom_read_byte((const uint8_t *)(offset + i));
		uart_printstr("boucle de comparaison\r\n");
		if (tmp != temp_buffer[i])
			break;
	}
	if (i == length + 1)
	{
		uart_printstr("was already written\r\n");
		return false;
	}
	else 	// ecrire dans l'eeprom
	{
		uart_printstr("n'etait pas dans l'eeprom\r\n");
		for (i = 0; i < length + 2 ; ++i)
		{
			uart_printstr("boucle d'ecriture\r\n");
			eeprom_write_byte((uint8_t *)(offset + i), temp_buffer[i]);
		}

	}

	// // test : imprimer le contenu de buffer
	// for (size_t i = 0; i < length + 2; i++) {
	// 	printf("%02X\n", temp_buffer[i]);
    // }

	// // for (size_t i = 0; i < length; i++) {
    // //     uint8_t tmp = buff[i];
	// // 	printf("%02X\n", tmp);
    // // }



	return true;
}

int main () {

	uart_init();

	char str[20] = "Hello world!\0";
	//uint16_t number = 0xFE42;

	safe_eeprom_write(str, 0, sizeof(str));
	_delay_ms(1000);
	safe_eeprom_write(str, 0, sizeof(str));

}