#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int int_to_bin(int k)
{
char *buffer = calloc(1000, 1);
itoa(k, buffer, 2);
return buffer;
}

int main()
{
	int magic = 0xFE42;
	int code = 0xAB;
	int agauche = 0xFE42AB;
	int adroite = 0xABFE42;
	printf("MAGIC X [%x]\n", magic);
	printf("MAGIC I [%i]\n", magic);
	printf("CODE X [%x]\n", code);
	printf("CODE I [%i]\n", code);
	printf("agauche I [%i]\n", agauche);
	printf("adroite I [%i]\n", adroite);
	printf("BIN MAGIC %s\n", int_to_bin(magic));
	printf("BIN code %s\n", int_to_bin(code));
	printf("BIN agauche %s\n", int_to_bin(agauche));
	printf("BIN adroite %s\n", int_to_bin(adroite));
}