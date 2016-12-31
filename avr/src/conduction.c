#include "conduction.h"

#include <inttypes.h>

#include "fixed.h"
#include "interpolate.h"

fixed_t T[Nx][Ny];
fixed_t T_old[Nx];

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

void conduction_compute(uint8_t cycles)
{
    while(cycles--) {
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
    }
}

void conduction_update_boundary(fixed_t *boundaryT)
{
    for (uint8_t y = 0; y < Ny; y++) {
        for (uint8_t x = 0; x < Nx; x++) {
            if (x == 0) {
                T[x][y] = interpolate(boundaryT[5], boundaryT[1], y, 24);
            }
            else if (x == Nx - 1) {
                T[x][y] = interpolate(boundaryT[2], boundaryT[4], y, 24);
            }
            else if (y == 0 && (x < (Nx >> 1))) {
                T[x][y] = interpolate(boundaryT[5], boundaryT[0], x, 32);
            }
            else if (y == 0) {
                T[x][y] = interpolate(boundaryT[0], boundaryT[2], x - 16, 32);
            }
            else if (y == Ny - 1 && (x < (Nx >> 1))) {
                T[x][y] = interpolate(boundaryT[1], boundaryT[3], x, 32);
            }
            else if (y == Ny - 1){
                T[x][y] = interpolate(boundaryT[3], boundaryT[4], x - 16, 32);
            }
        }
    }
}
