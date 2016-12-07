// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.

#include <stdint.h>

#include "fixed.h"
#include "spi.h"
#include "adc.h"
#include "rgb_matrix.h"

#define Nx  32
#define Ny  24

/* void assign_color(float T, float Tmin, float Tmax){ */
/*     // Assign a color to a given temperature using the coolwarm colormap. */
/*     // http://www.kennethmoreland.com/color-maps/ */

/*     float scale[34] = {0, 0.03125, 0.0625, 0.09375, 0.125, 0.15625, 0.1875, 0.21875, 0.25, 0.28125, 0.3125, 0.34375, 0.375, 0.40625, 0.4375, 0.46875, 0.5, 0.53125, 0.5625, 0.59375, 0.625, 0.65625, 0.6875, 0.71875, 0.75, 0.78125, 0.8125, 0.84375, 0.875, 0.90625, 0.9375, 0.96875, 1}; */
/*     int reds[34] = {59,68,77,87,98,108,119,130,141,152,163,174,184,194,204,213,221,229,236,241,245,247,247,247,244,241,236,229,222,213,203,192,180}; */
/*     int greens[34] = {76, 90, 104, 117, 130, 142, 154, 165, 176, 185, 194, 201, 208, 213, 217, 219, 221, 216, 211, 204, 196, 187, 177, 166, 154, 141, 127, 112, 96, 80, 62, 40, 4}; */
/*     int blues[34] = {192, 204, 215, 225, 234, 241, 247, 251, 254, 255, 255, 253, 249, 244, 238, 230, 221, 209, 197, 185, 173, 160, 148, 135, 123, 111, 99, 88, 77, 66, 56, 47, 38}; */

/*     int index = 0; */
/*     float ratio = (T - Tmin) / (Tmax - Tmin); */
/*     for (int i=0; i<34; i++){ */
/*         if (ratio < scale[i]){ */
/*             index = i; */
/*             break; */
/*         } */
/*     } */


/*     int color[3] = {reds[index], blues[index], greens[index]}; */
/* } */

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
    // alpha = 0.001 * 1000
    //
    // dt is time step size (s)
    // dt = 1
    //
    // dx is distance between LEDs (m),
    // dx = 10
    //
    // Tao = (alpha * dt) / (dx ^ 2)
    // tao = (1 * 1) / (10 ^2)
    // tao = 0.01
    fixed_t tao = fixed_from_real(0.01);

    // Time loop
//    for (uint16_t n=0; n < 10000; n++) {
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
                /* assign_color(T[i][j], 40.0, 50.0); */
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
        for (uint16_t i = 0; i < 728; i++)
        {
	    // convert to color

            rgb_matrix_send_pixel(i & 0x00FF, (i & 0x0FF0) >> 4, (i & 0xFF00) >> 8);
        }
        rgb_matrix_end_frame();
    }

    return 0;
}
