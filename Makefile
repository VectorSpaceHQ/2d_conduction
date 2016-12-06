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

all: $(TARGET)

conduction.c: fixed.h spi.h adc.h rgb_matrix.h
spi.c: spi.h
adc.c: adc.h
rgb_matrix.c: rgb_matrix.h

$(TARGET): conduction.c spi.c adc.c rgb_matrix.c gcrt1.S
	$(CC) -mmcu=$(DEVICE) $(CFLAGS) $^ -o $(TARGET)
	avr-size $(TARGET)

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(TARGET).map
