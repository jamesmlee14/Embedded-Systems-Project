# File:   Makefile
# Author: James Mitchum Lee (jml184)
# Date:   4 October 2019
# Descr:  Makefile for Rock Paper Scissors BO5

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out

# Compile: create object files from C source files.
game.o: game.c bitmap.h player_assignment.h selection.h transmission.h outcome.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/navswitch.h ../../drivers/avr/ir_uart.h ../../drivers/led.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

bitmap.o: bitmap.c bitmap.h ../../drivers/navswitch.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

player_assignment.o: player_assignment.c player_assignment.h bitmap.h ../../drivers/avr/system.h ../../drivers/led.h ../../drivers/button.h ../../drivers/avr/ir_uart.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

selection.o: selection.c selection.h bitmap.h ../../drivers/led.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

transmission.o: transmission.c transmission.h bitmap.h ../../drivers/avr/ir_uart.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

outcome.o: outcome.c outcome.h bitmap.h ../../drivers/led.h

# Link: create ELF output file from object files.
game.out: game.o system.o timer.o pacer.o pio.o navswitch.o ir_uart.o usart1.o timer0.o prescale.o led.o button.o bitmap.o player_assignment.o selection.o transmission.o outcome.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


