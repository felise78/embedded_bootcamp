TARGET		=	setup
CC			=	avr-gcc

BIN_FILE	=	$(TARGET).bin
HEX_FILE	=	$(TARGET).hex

CFLAGS		=	-mmcu=atmega328p -Os -DF_CPU=16000000UL -DBAUDRATE=115200

SRC			=	main.c \
				utils.c \
				uart.c	\
				i2c.c

all: hex flash 

hex : $(HEX_FILE)

$(BIN_FILE): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET).bin $^

$(HEX_FILE): $(BIN_FILE)
	avr-objcopy -O ihex -R .eeprom $(TARGET).bin $@

flash:
	screen -X quit &> /dev/null || true
	sleep 1
	avrdude -c arduino -b 115200 -p atmega328p -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex
	gnome-terminal -- screen /dev/ttyUSB0 115200

clean:
	rm -f $(TARGET).bin $(TARGET).hex