// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.
// Vector Space, 12/16
// Goulder, Spontarelli, Thomas

#include <stdint.h>

#include "fixed.h"
#include "spi.h"
#include "adc.h"
#include "rgb_matrix.h"
#include "colormap.h"

#define Nx  32
#define Ny  24

volatile fixed_t T[Nx][Ny];
volatile fixed_t T_old[Nx];

void update_boundary(void)
{
    fixed_t Ttop = adc_read(0);
    fixed_t Tleft = adc_read(1);
    fixed_t Tbottom = adc_read(2);
    fixed_t Tright = adc_read(3);
    fixed_t Tavg = (Ttop + Tleft + Tbottom + Tright) >> 2;

    // initial conditions
    for (uint8_t y = 0; y < Ny; y++) {
        for (uint8_t x = 0; x < Nx; x++) {
            if (x == 0) {
                T[x][y] = Tleft;
            }
            else if (x == Nx - 1) {
                T[x][y] = Tright;
            }
            else if (y == 0) {
                T[x][y] = Ttop;
            }
            else if (y == Ny - 1) {
                T[x][y] = Tbottom;
            }
            else {
                //T[x][y] = Tavg;
            }
        }
    }
}

__attribute__ (( OS_main ))
int main()
{
    spi_master_init();

    // alpha is thermal diffusivity (m^2/s)
    // alpha(copper) = 1.11x10^-4 m^2/s
    //
    // dt is time step size (s)
    // dt = 0.1 s
    //
    // dx is distance between LEDs (m),
    // dx = 0.0115 m
    //
    // tao = (alpha * dt) / (dx ^ 2)
    // tao = (0.000111 * 0.1) / (0.0115 ^ 2)
    // tao = 0.08
    fixed_t tao = fixed_from_real(0.08);

    // Time loop
    while(1) {

        update_boundary();

        // Store temperature array as old values for use in explicit method
        for (uint8_t i=1; i < Nx - 1; i++) {
            T_old[i] = T[i][0];
        }
        T_old[0] = T[0][1];
        T_old[Nx -1] = T[Nx - 1][1];

        // Euler explicit method
        for (uint8_t j=1; j < Ny - 1; j++) {
            for (uint8_t i=1; i < Nx - 1; i++) {
                fixed_t term =     fixed_mul(tao,
                                            T[i+1][j] + T_old[i-1] + T_old[i] + T[i][j+1]
                                        -   (T[i][j] << 2)
                                    )
                                +   T[i][j];
                T_old[i] = T[i][j];
                T[i][j] = term;
            }

            T_old[0] = T[0][j + 1];
            T_old[Nx - 1] = T[Nx - 1][j + 1];
        }

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

    return 0;
}
