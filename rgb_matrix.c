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
    spi_transfer(0xFF);
    spi_transfer(0x00);
    spi_transfer(0x00);
    spi_transfer(0x00);
}

void rgb_matrix_get_xy_from_num(uint16_t num, uint8_t *x, uint8_t *y)
{
    uint8_t y_base =  num >> 8;
    uint8_t y_offset = (num >> 3) & 0x0007;

    *y = (y_base << 3) + y_offset;

    uint8_t x_base = ((num >> 6) & 0x0003) << 3;
    if (y_base & 0x01) {
        x_base = 24 - x_base;
    }

    uint8_t x_offset = num & 0x0007;
    if (y_offset & 0x01) {
        x_offset = 7 - x_offset;
    }

    *x = x_base + x_offset;
}
