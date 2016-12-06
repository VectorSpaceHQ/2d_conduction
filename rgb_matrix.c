#include "rgb_matrix.h"
#include "spi.h"

void rgb_matrix_start_frame(void)
{
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);
}

void rgb_matrix_send_pixel(uint8_t r, uint8_t g, uint8_t b)
{
    spi_transfer(0xE1);
    spi_transfer(b);
    spi_transfer(g);
    spi_transfer(r);
}

void rgb_matrix_end_frame(void)
{
    spi_transfer(0x00);
    spi_transfer(0xFF);
    spi_transfer(0xFF);
    spi_transfer(0xFF);
}
