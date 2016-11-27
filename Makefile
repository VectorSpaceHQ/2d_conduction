
all: conduction conduction-avr

conduction:
	g++ conduction.c -o conduction

conduction-avr:
	avr-g++ -Os -mmcu=atmega328p conduction.c -o conduction-avr
	avr-size conduction-avr

clean:
	rm -f conduction conduction-avr
