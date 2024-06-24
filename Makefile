DEVICE     = atmega328p

CLOCK      = 9830400

PROGRAMMER = -c usbtiny -P usb

OBJECTS    = myprogram . o myfunctions . o

FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0xe0:m

build:
	avr-gcc -Wall -Os -DF_CPU=${CLOCK} -mmcu=${DEVICE} -c main.c lcd.c
	avr-gcc -Wall -DF_CPU=${CLOCK} -mmcu=${DEVICE} -o main.elf main.o lcd.o
	avr-objcopy -O ihex main.elf main.hex
	rm main.o
	rm main.elf 

flash: build
	avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB0 -b 57600 -U flash:w:main.hex || avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB1 -b 57600 -U flash:w:main.hex 
