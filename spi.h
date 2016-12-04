#ifndef SPI_H
#define SPI_H

#include <inttypes.h>

void spi_master_init(void);
uint8_t spi_transfer(uint8_t tx);

#endif // SPI_H
