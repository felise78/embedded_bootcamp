#include "main.h"

bool strcmp_cheatcode(char *str)
{
    char cheatcode[MAX - 1] = "#FULLRAINBOW";
    // uart_printstr("cheatcode : ");
    // uart_printstr(cheatcode);
    // uart_printstr("\r\nstr: ");
    // uart_printstr("\r\n");
    uint8_t i = 0;
    while (i < MAX - 1)
    {
        if (cheatcode[i] != str[i])
            return false;
        i++;
    }
    return true;
}

bool parse(char *color)
{
    int i = 0;
    if (color[0] != '#')
        return false;
    while (++i < 7)
    {
        if ((color[i] < '0' || (color[i] > '9' && color[i] < 'A') || color[i] > 'F'))
            return false;
    }
    if (color[7] != 'D')
        return false;
    if (color[8] < '6' || color[8] > '8')
        return false;
    return true;
}
