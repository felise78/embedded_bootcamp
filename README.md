# 🔌 Embedded Bootcamp - ATmega328p

A comprehensive training program for embedded programming on ATmega328p microcontroller, organized in 9 progressive learning days.

## 📋 Overview

This bootcamp covers the fundamental concepts of embedded programming on ATmega328p microcontroller (used in Arduino Uno). Each day includes several practical exercises with increasing difficulty levels.

## 🎯 Learning Objectives

- Master low-level C programming for microcontrollers
- Understand ATmega328p architecture and peripherals
- Manipulate registers and input/output ports
- Implement communication protocols (UART, I2C, SPI)
- Use timers and PWM signal generation
- Handle analog-to-digital conversions (ADC)
- Interact with sensors and actuators

## 🗓️ Bootcamp Program

### Day 00 - Premiers programmes
- **ex00**: Development environment setup
- **ex01**: Basic port manipulation
- **ex02**: Digital input reading (button)
- **ex03**: Combined input/output management
- **ex04**: Binary counter with buttons and LEDs

### Day 01 - Timers
- **ex00**: Timed LED blinking
- **ex01**: PWM introduction with Timer 1
- **ex02**: PWM with different duty cycles
- **ex03**: Interactive PWM control

### Day 02 - Interruptions
- **ex00**: Advanced PWM
- **ex01**: Complex pulse width modulation

### Day 03 - UART Protocol
- **ex00**: UART initialization
- **ex01**: Serial data transmission
- **ex02**: Bidirectional communication
- **ex03**: Advanced communication protocol
- **ex04**: Communication error handling

### Day 04 - Protocol I2C
- **ex00**: I2C protocol basics
- **ex01**: Communication with AHT20 sensor (temperature/humidity)
- **ex02**: Continuous sensor data reading

### Day 05 - EEPROM Memory
- **ex00**: Basic EEPROM read/write
- **ex01**: Persistent data management
- **ex02**: Serial communication with EEPROM data

### Day 06 - RGB LEDs and Advanced PWM
- **ex00**: Basic RGB LED control
- **ex01**: Color sequences
- **ex02**: PWM for RGB LED
- **ex03**: RGB control via UART

### Day 07 - Analog-to-Digital Conversion (ADC)
- **ex00**: ADC initialization and reading
- **ex01**: Potentiometer reading
- **ex02**: Multi-sensor reading (potentiometer, LDR, NTC)
- **ex03**: ADC with serial display
- **ex04**: ADC-based color wheel

### Day 08 - SPI Communication and Integration
- **ex00**: SPI protocol basics
- **ex01**: SPI data transmission
- **ex02**: SPI peripheral control
- **ex03**: SPI with ADC integration
- **ex04**: Complete SPI communication system
- **ex05**: Final SPI project

## 🛠️ Technical Requirements

### Required Hardware
- ATmega328p microcontroller (or Arduino Uno board)
- LEDs, resistors, push buttons
- RGB LED
- Potentiometer, photoresistor (LDR), thermistor (NTC)
- AHT20 temperature/humidity sensor
- Breadboard and connecting wires
- AVR programmer or USB cable (for Arduino)

### Required Software
- **avr-gcc**: Compiler for AVR microcontrollers
- **avrdude**: Programming tool
- **screen**: Serial terminal for communication
- Code editor (VS Code recommended)

### Tool Installation (Linux)
```bash
sudo apt-get update
sudo apt-get install gcc-avr avr-libc avrdude screen
```

## 🚀 Usage

### Compilation and Programming
```bash
cd Day01/ex00/
make          # Compile the project
make flash    # Program the microcontroller
make clean    # Clean temporary files
```

### Makefile Configuration
Makefiles are configured for:
- **Microcontroller**: ATmega328p
- **Frequency**: 16 MHz
- **Programmer**: Arduino (via /dev/ttyUSB0)
- **Baudrate**: 115200

## 📡 Serial Communication

For exercises using UART:
```bash
screen /dev/ttyUSB0 115200
```

Exit screen: `Ctrl+A` then `K` then `Y`

## 📚 Resources

### Included Documentation
- `ATmega328p.pdf`: Official microcontroller datasheet
- `schema.pdf`: Electrical schematics
- `AHT20-datasheet-*.pdf`: AHT20 sensor documentation
- `ADC.pdf`: Guide on analog-to-digital conversions
- PDF guides for each day (`day_*.fr.pdf`)

### Covered Concepts
- **Registers**: DDRX, PORTX, PINX for port management
- **Timers**: TCCR1A/B, OCR1A, ICR1 for PWM and timing
- **UART**: UDR0, UBRR0, UCSR0A/B/C for serial communication
- **I2C/TWI**: TWCR, TWDR, TWSR for I2C communication
- **ADC**: ADMUX, ADCSRA, ADCL/H for analog conversion
- **EEPROM**: eeprom_read/write_byte() functions