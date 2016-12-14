// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.
// Vector Space, 12/16
// Goulder, Spontarelli, Thomas

#include <inttypes.h>

#include "fixed.h"
#include "spi.h"
#include "adc.h"
#include "rgb_matrix.h"
#include "colormap.h"
#include "conduction.h"

void update_leds(void);
void read_temperatures(fixed_t *boundaryT);

__attribute__ (( OS_main ))
int main()
{
    fixed_t boundaryT[4];

    spi_master_init();

    while(1) {
        read_temperatures(boundaryT);
        conduction_update_boundary(boundaryT);
        conduction_compute(1);
        update_leds();
    }

    return 0;
}

void read_temperatures(fixed_t *boundaryT)
{
    for (uint8_t i = 0; i < 4; i++) {
        boundaryT[i] = adc_read(i);
    }
}

void update_leds(void)
{
    rgb_matrix_start_frame();

    for (uint16_t i = 0; i < Nx * Ny; i++) {

        uint8_t x, y;
        rgb_matrix_get_xy_from_num(i, &x, &y);

        uint8_t r, g, b;
        colormap_temperature_to_rgb(T[x][y], &r, &g, &b);

        rgb_matrix_send_pixel(r, g, b);
    }

    rgb_matrix_end_frame();
}
