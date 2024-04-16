TARGET		=	setup
CC			=	avr-gcc

BIN_FILE	=	$(TARGET).bin
HEX_FILE	=	$(TARGET).hex

# -DF_CPU=16000000UL difinit la frequence du microcontroleur a 16MHz
# La directive -D dans les options de compilation (CFLAGS) est utilisée pour définir 
# des macros au niveau du préprocesseur. Cela définit une macro appelée F_CPU avec une 
# valeur de 16000000UL.

# Cette macro est souvent utilisée dans les programmes pour spécifier la fréquence 
# du CPU, ce qui est important pour certaines opérations de synchronisation ou de 
# temporisation, par exemple dans le calcul du délai dans les fonctions comme delay() 
# dans les programmes Arduino.

CFLAGS		=	-mmcu=atmega328p -Os -DF_CPU=16000000UL

# Le drapeau -Os dans les options de compilation indique au compilateur de "taille 
# d'optimisation" (gcc) d'optimiser le code pour la taille plutôt que pour la vitesse 
# d'exécution. Cela signifie qu'il va essayer de produire un code compilé plus petit,
# même si cela peut entraîner une légère baisse des performances par rapport à 
# l'optimisation pour la vitesse (-O2 ou -O3, par exemple).

# L'optimisation de la taille peut être importante dans les applications embarquées 
# où l'espace mémoire est limité, comme dans le cas des microcontrôleurs AVR comme 
# l'ATmega328P mentionné dans votre exemple. Cela permet de réduire la taille du code 
# généré, ce qui peut être crucial lorsque la mémoire flash disponible est limitée.

SRC			=	main.c

all: $(BIN_FILE) $(HEX_FILE) flash 

$(BIN_FILE): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET).bin $^

$(HEX_FILE): $(BIN_FILE)
	avr-objcopy -O ihex -R .eeprom $(TARGET).bin $@

# flashe le microcontrôleur
flash:
	avrdude -c arduino -b 115200 -p atmega328p -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex

clean:
	rm -f $(TARGET).bin $(TARGET).hex