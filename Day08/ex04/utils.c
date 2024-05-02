#include "main.h"

void    print_number(uint32_t x) {
    char base[10] = "0123456789";
    if (x >= 10)
        print_number(x / 10);
    uart_tx(base[x % 10]);
}

uint8_t charToHex(char value) {
  if (value >= '0' && value <= '9') return value - '0';
  else if (value >= 'A' && value <= 'F') return value - 'A' + 10;
}

uint8_t hexToDec(char hex1, char hex2) {
    uint8_t dec1 = charToHex(hex1);
    uint8_t dec2 = charToHex(hex2);
    return dec1 * 16 + dec2;
}