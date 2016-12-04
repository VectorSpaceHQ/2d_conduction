TARGET = conduction
AVR_TARGET = $(TARGET)-avr

AVR_DEVICE = atmega328p

AVR_CC = avr-gcc

CFLAGS += -std=gnu99
CFLAGS += -Os

AVR_CFLAGS += $(CFLAGS)
AVR_CFLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
AVR_CFLAGS += -Wl,-Map=$(AVR_TARGET).map

all: $(TARGET) $(AVR_TARGET)

conduction.c: fixed.h

$(TARGET): conduction.c
	$(CC) $(CFLAGS) conduction.c -o $(TARGET)

$(AVR_TARGET): conduction.c
	$(AVR_CC) -mmcu=$(AVR_DEVICE) $(AVR_CFLAGS) conduction.c -o $(AVR_TARGET)
	avr-size $(AVR_TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(AVR_TARGET) $(AVR_TARGET).map
