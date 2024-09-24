DEVICE     = atmega328p

CLOCK      = 9830400

# PROGRAMMER = -c usbtiny -P usb

# OBJECTS    = myprogram . o myfunctions . o

# FUSES      = -U hfuse:w:0xd9:m -U lfuse:w:0xe0:m

SRCS = main.c lcd.c i2c.c BME68x_SensorAPI/bme68x.c uart.c
OBJS = main.o lcd.o i2c.o bme68x.o uart.o

build:
	avr-gcc -Wall -Os -DF_CPU=${CLOCK} -mmcu=${DEVICE} -c ${SRCS}
	avr-gcc -Wall -DF_CPU=${CLOCK} -mmcu=${DEVICE} -o main.elf ${OBJS}
	avr-objcopy -O ihex main.elf main.hex
	rm ${OBJS}
	rm main.elf 

flash: build
	avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB0 -b 57600 -U flash:w:main.hex || avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB1 -b 57600 -U flash:w:main.hex 

clean:
	rm ${OBJS}
	rm main.elf

buildTWITest:
	avr-gcc -Wall -Os -DF_CPU=14745600 -mmcu=${DEVICE} -c twitest.c
	avr-gcc -Wall -DF_CPU=14745600UL -mmcu=${DEVICE} -o main.elf twitest.o
	avr-objcopy -O ihex main.elf main.hex
	avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB0 -b 57600 -U flash:w:main.hex || avrdude -c arduino -p ${DEVICE} -P /dev/ttyUSB1 -b 57600 -U flash:w:main.hex 

