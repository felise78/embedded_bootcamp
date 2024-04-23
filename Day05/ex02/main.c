#include "main.h"

#include <stdio.h>
#include <stdint.h>

#define EEPROM_SIZE 1024

// 1024 octets de memoire EEPROM

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
		int j = i - 2;
		temp_buffer[i] = buff[j];
	}	


	// test : imprimer le contenu de buffer

	for (size_t i = 0; i < length + 2; i++) {
		printf("%02X\n", temp_buffer[i]);
    }

	// for (size_t i = 0; i < length; i++) {
    //     uint8_t tmp = buff[i];
	// 	printf("%02X\n", tmp);
    // }

	// uint16_t magic = 0xFE42;

	// uint8_t tmp_data;

	// size_t i = 0;
	// uint8_t tmp_eeprom;
	// tmp_eeprom = eeprom_read_byte((uint8_t *)offset);
	// // verifier la memoire a cet emplacement
	// // ne pas reecrire si c'est la meme chose
	// while (strncmp(tmp_eeprom, buffer));

	// // if nombre magic est dans buffer
	// eeprom_read_block(&tmp, buffer, length + sizeof(uint32_t));
	// if((tmp << 16) == MAGICNUMBER)
	// {
	// 	for (int i = 0; i < 5; i++)
	// 	{
	// 		PORTD = (1 << 6);
	// 		_delay_ms(100);
	// 		PORTD = (1 << 3);
	// 		_delay_ms(100);
	// 	}
	// 	// on peut write car c'est a nous
	// }
	// else
	// {

	// 	*(uint32_t*)buffer = ((*(uint32_t*)buffer << 16) | MAGICNUMBER);

	// }
	// // 0xAB != 0xFE42
	// // else
	// // on ecrite le magic number
	// // et on write car c'est a nous mtn
	return true;
}

int main () {

	char str[20] = "Hello world!\0";
	uint16_t number = 0xFE42;

	safe_eeprom_write(&number, 0, sizeof(number));

}