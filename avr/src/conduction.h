#ifndef CONDUCTION_H
#define CONDUCTION_H

#include "fixed.h"

#define Nx  32
#define Ny  24

extern fixed_t T[Nx][Ny];
extern fixed_t T_old[Nx];

void conduction_compute(uint8_t cycles);
void conduction_update_boundary(fixed_t Ttop, fixed_t Tleft, fixed_t Tbottom, fixed_t Tright);

#endif // CONDUCTION_H
