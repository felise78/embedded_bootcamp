#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define MAX 13

bool strcmp_cheatcode(char *str)
{
    char cheatcode[MAX - 1] = "#FULLRAINBOW";
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
    if (color[8] < '6' || color[9] > '8')
        return false;
    return true;
}

void set_LEDS(char* color, bool rainbow)
{
    if (rainbow)
    {
        printf("\x1b[2J\x1b[H");
        printf("Rainbow wheel function\r\n");
        return;
    }
    if (color[8] == '6')
    {
        printf("\x1b[2J\x1b[H");
        printf("SET led D6\r\n");
    }
    else if (color[8] == '7')
    {
        printf("\x1b[2J\x1b[H");
        printf("SET led D7\r\n");
    }
    else
    {
        printf("\x1b[2J\x1b[H");
        printf("SET led D8\r\n");
    }
}

// utiliser un interrupt pour cet exo

int main ()
{

    int i = 0;
    char color[MAX];
    char buffer[2]; 

    printf("Enter a value #RRGGBBDD : \r\n");
    while (i < MAX && fgets(buffer, sizeof(buffer), stdin) != NULL && buffer[0] != 0) {

        if (buffer[0] == '\n')
        {   
            if (strcmp_cheatcode(color))
            {
                printf("cheatcode ok\r\n");
                set_LEDS("", 1);    // programme
            }
            else if (parse(color) && i < 10)
            {
                printf("format ok\r\n");
                set_LEDS(color, 0); // programme
            }
            else
            {
                printf("\x1b[2J\x1b[H");
                printf("Enter a value #RRGGBBDD : \r\n");
                i = 0;
            }
        }
        else
        {
            // uart_tx();
            color[i] = buffer[0];
            i++;
        }
    }
    if (i == MAX)
    {
        printf("\x1b[2J\x1b[H");
        printf("Enter a value #RRGGBBDD : \r\n");
        i = 0;
    }
}
 /*   
    char color[MAX];
    while (1)
    {
        char c = uart_rx();
        if (c != 0 && i < MAX)
        {
            if (c == '\r')
            {   
                printf("rentre ici\r\n");
                printf(color);
                uart_tx(color[MAX - 1] + 48);
                
                if (strcmp_cheatcode(color))
                {
                    printf("cheatcode ok\r\n");
                    // programme
                }
                else
                {
                    printf("\x1b[2J\x1b[H");
                    printf("Enter a value #RRGGBBDD : \r\n");
                    i = 0;
                }
            }
            else
            {
                uart_tx(c);
                color[i] = c;
                i++;
            }
        }
        if (i == MAX)
        {
            printf("\x1b[2J\x1b[H");
            printf("Enter a value #RRGGBBDD : \r\n");
            i = 0;
        }
    }
    return 0;
}*/