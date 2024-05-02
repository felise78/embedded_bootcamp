// #include <stdio.h>
#include "main.h"

void    print_number(uint8_t x) {
    char base[10] = "0123456789";
    if (x >= 10)
        print_number(x / 10);
    uart_tx(base[x % 10]);
}

void print_hex_value(char c) {

	unsigned char titouan = c;
	static char buffer[3] = { '0', '0', '\0'};
    int i =  sizeof(buffer) - 1;
	do {
		buffer[--i] = "0123456789ABCDEF"[titouan & 0x0f];
		titouan >>= 4;
	} while (titouan);
	uart_printstr(buffer);
}

//printf("%s\n", buffer);

// int main()
// {
// 	print_hex_value(128);
// }