#ifndef SPI_H
#define SPI_H

#include <inttypes.h>

#ifdef __AVR
void spi_master_init(void);
uint8_t spi_transfer(uint8_t tx);
#else
#define spi_master_init()
#define spi_transfer(x)
#endif

#endif // SPI_H
