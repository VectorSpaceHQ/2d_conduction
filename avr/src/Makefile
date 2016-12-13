TARGET = conduction
DEVICE = atmega328p

CC = avr-gcc

CFLAGS += -std=gnu99
CFLAGS += -Os
CFLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
CFLAGS += -Wl,-Map=$(TARGET).map
CFLAGS += -flto
CFLAGS += -mrelax
CFLAGS += -lm
CFLAGS += -nostartfiles
CFLAGS += -g3
CFLAGS += -DNO_VECTORS

INCLUDES += -I startup/common

all: $(TARGET)

conduction.c: fixed.h spi.h adc.h rgb_matrix.h
spi.c: spi.h
adc.c: adc.h
rgb_matrix.c: rgb_matrix.h

$(TARGET): conduction.c spi.c adc.c rgb_matrix.c startup/crt1/gcrt1.S
	$(CC) -mmcu=$(DEVICE) $(CFLAGS) $(INCLUDES) $^ -o $(TARGET)
	avr-size $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

load: $(TARGET)
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex:i

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(TARGET).map $(TARGET).hex
