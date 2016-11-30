
all: conduction conduction-avr

conduction: conduction.c
	gcc conduction.c -std=gnu99 -o  conduction

conduction-avr: conduction.c
	avr-gcc -std=gnu99 -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,-Map=conduction.map conduction.c -o conduction-avr
	avr-size conduction-avr

clean:
	rm -f conduction conduction-avr
