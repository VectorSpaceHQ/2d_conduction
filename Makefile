TARGET = conduction
DEVICE = atmega328p

CC = avr-gcc

CFLAGS += -std=gnu99
CFLAGS += -Os
CFLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
CFLAGS += -Wl,-Map=$(TARGET).map
CFLAGS += -lm

all: $(TARGET)

conduction.c: fixed.h spi.h adc.h
spi.c: spi.h
adc.c: adc.h

$(TARGET): conduction.c spi.c adc.c
	$(CC) -mmcu=$(DEVICE) $(CFLAGS) $^ -o $(TARGET)
	avr-size $(TARGET)

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(TARGET).map
