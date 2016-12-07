// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.
// Vector Space, 12/16
// Goulder, Spontarelli, Thomas

#include <stdint.h>

#include "fixed.h"
#include "spi.h"
#include "adc.h"
#include "rgb_matrix.h"

#define Nx  32
#define Ny  24

volatile fixed_t T[Nx][Ny];
volatile fixed_t T_old[Nx];


void assign_color_adam(int16_t T, int16_t Tmax, int16_t Tmin, uint8_t* R, uint8_t* G, uint8_t* B ){
    uint8_t red = (-484*T)*T*T + (207*T)*T + 292*T + 58;
    uint8_t green = (-76*T)*T*T - (577*T)*T + 598*T + 68;
    uint8_t blue = (612*T)*T*T - (1345*T)*T + 586*T + 184;
    *R = red;
    *G = green;
    *B = blue;
}

void assign_color( int16_t T, int16_t Tmax, int16_t Tmin, uint8_t* R, uint8_t* G, uint8_t* B ){
    uint8_t index = (T - Tmin) * 34 / (Tmax - Tmin);
    unsigned int reds[34] = {59,68,77,87,98,108,119,130,141,152,163,174,184,194,204,213,221,229,236,241,245,247,247,247,244,241,236,229,222,213,203,192,180};
    unsigned int greens[34] = {76, 90, 104, 117, 130, 142, 154, 165, 176, 185, 194, 201, 208, 213, 217, 219, 221, 216, 211, 204, 196, 187, 177, 166, 154, 141, 127, 112, 96, 80, 62, 40, 4};
    unsigned int blues[34] = {192, 204, 215, 225, 234, 241, 247, 251, 254, 255, 255, 253, 249, 244, 238, 230, 221, 209, 197, 185, 173, 160, 148, 135, 123, 111, 99, 88, 77, 66, 56, 47, 38};

    *R = reds[index];
    *G = greens[index];
    *B = blues[index];
}


void transfer_colors(volatile fixed_t T[Nx][Ny]){
    // This function takes the entire temperature array and transfers it
    // to the LED matrix.
    //
    // Because Jordan soldered the LED matrix without care and respect for the
    // rest of us, a significant amount of mapping has to be done from the
    // temperature array to the LED layout.
    // The snakelike path below assumes:
    //     T[0][0] is at lower right
    //     T[Nx][0] is lower left
    //     T[0][Ny] is upper right

    uint8_t Tmax = 1;
    uint8_t Tmin = 0;
    uint8_t iforward = -1;
    uint8_t kforward = 1;
    uint8_t column = 0;
    uint8_t row = 0;
    uint8_t R, G, B;

    for (uint8_t k = 0; k < 12; k++) {
        for (uint8_t j = 0; j < 8; j++) {
            iforward = iforward * -1;
            if (iforward > 0){
                for (uint8_t i = 0; i < 8; i++) {
                    uint8_t x = i + (8 * column);
                    uint8_t y = j + (8 * row);
                    // send color of T[x][y] here
                    assign_color_adam( T[x][y], Tmax, Tmin, &R, &G, &B );
                    rgb_matrix_send_pixel(R, G, B);
                }
            }
            else{
                for (uint8_t i = 7; i >= 0; i--) {
                    uint8_t x = i + (8 * column);
                    uint8_t y = j + (8 * row);
                    // send color of T[x][y] here
                    assign_color_adam( T[x][y], Tmax, Tmin, &R, &G, &B );
                    rgb_matrix_send_pixel(R, G, B);
                }
            }
        }
        if ((k+1) % 4 == 0){
            kforward = kforward * -1;
            row += 1;
            column = column - kforward;
        }
        column = column + kforward;
    }
}

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
    // dt = .1 s
    //
    // dx is distance between LEDs (m),
    // dx = .0115 m
    //
    // Tao = (alpha * dt) / (dx ^ 2)
    // tao = (.000111 * .1) / (.0115 ^2)
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
        transfer_colors(T);
        rgb_matrix_end_frame();
    }

    return 0;
}
