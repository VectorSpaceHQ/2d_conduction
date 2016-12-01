
all: conduction conduction-avr

conduction: conduction.c
	g++ conduction.c -o conduction

conduction-avr: conduction.c
	avr-g++ -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,-Map=conduction.map conduction.c -o conduction-avr
	avr-size conduction-avr

clean:
	rm -f conduction conduction-avr
