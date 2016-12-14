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
CFLAGS += -DF_CPU=16000000

INCLUDES += -I startup/common

all: $(TARGET)

main.c: fixed.h spi.h adc.h rgb_matrix.h colormap.h conduction.h timer.h
spi.c: spi.h
adc.c: adc.h
rgb_matrix.c: rgb_matrix.h
colormap.c: colormap.h fixed.h
conduction.c: conduction.h fixed.h
timer.c: timer.h

$(TARGET): main.c spi.c adc.c rgb_matrix.c colormap.c conduction.c timer.c startup/crt1/gcrt1.S
	$(CC) -mmcu=$(DEVICE) $(CFLAGS) $(INCLUDES) $^ -o $(TARGET)
	avr-size $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

load: $(TARGET)
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex:i

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(TARGET).map $(TARGET).hex
