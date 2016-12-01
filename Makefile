
all: conduction conduction-avr

conduction: conduction.c fixed.h
	g++ conduction.c -o conduction

conduction-avr: conduction.c fixed.h
	avr-g++ -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,-Map=conduction.map conduction.c -o conduction-avr
	avr-size conduction-avr

clean:
	rm -f conduction conduction-avr
