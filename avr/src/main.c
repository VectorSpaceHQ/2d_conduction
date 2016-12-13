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

__attribute__ (( OS_main ))
int main()
{
    spi_master_init();

    while(1) {
        conduction_update_boundary(adc_read(0), adc_read(1), adc_read(2), adc_read(3));
        conduction_compute(1);
        update_leds();
    }

    return 0;
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
