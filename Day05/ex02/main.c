#include "main.h"

#include <stdio.h>
#include <stdint.h>

// 1024 octets de memoire EEPROM

// bool safe_eeprom_read(void *buffer, size_t offset, size_t length)

bool safe_eeprom_write(void *buffer, size_t offset, size_t length)
{
	(void)offset;
	(void)length;

	// test imprimer le contenu de buffer
	uint8_t *tmp = (uint8_t*)buffer;
	//printf("%02X\n", tmp);

	// size_t i = 1;
	// tmp = *((uint8_t*)buffer + i);
	// printf("%02X\n", tmp);

	for (size_t i = 0; i < length; i++) {
        printf("%02X\n", tmp[i]);
    }

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
	int number = 0xFE42;

	safe_eeprom_write(str, 0, sizeof(str));

}