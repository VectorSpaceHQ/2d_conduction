
#ifndef __AVR
#include <stdio.h>
#define dbg(...)  fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

#include <stdint.h>

#define Nx  32
#define Ny  24


#ifndef __AVR

void printT(volatile uint8_t T[Nx][Ny])
{
    for (uint8_t y = 0; y < Ny; y++)
    {
        for (uint8_t x = 0; x < Nx; x++)
        {
            dbg("%d ", T[x][y]);
        }
        dbg("\n");
    }
}

#else
#define printT(x)
#endif

int main(void)
{
    volatile uint8_t T[Nx][Ny];

    dbg("2D Conduction\n");

    uint8_t Ttop = 90;
    uint8_t Tleft = 90;
    uint8_t Tbottom = 80;
    uint8_t Tright = 90;

    uint8_t Tavg = (Ttop + Tleft + Tbottom + Tright) >> 2;

    for (uint8_t y = 0; y < Ny; y++)
    {
        for (uint8_t x = 0; x < Nx; x++)
        {
            if (x == 0)
            {
                T[x][y] = Tleft;
            }
            else if (x == Nx - 1)
            {
                T[x][y] = Tright;
            }
            else if (y == 0)
            {
                T[x][y] = Ttop;
            }
            else if (y == Ny - 1)
            {
                T[x][y] = Tbottom;
            }
            else
            {
                T[x][y] = Tavg;
            }
        }
    }

    dbg("\nInitial state\n");
    printT(T);

    for (uint16_t n = 0; n < 100; n++)
    {
        for (uint8_t y = 1; y < Ny - 1; y++)
        {
            for (uint8_t x = 1; x < Nx - 1; x++)
            {
                uint16_t sum = (uint16_t)(T[x - 1][y] + T[x + 1][y] + T[x][y - 1] + T[x][y + 1]) >> 2;
                T[x][y] = (uint8_t) sum;
            }
        }
    }

    dbg("\nFinal state\n");
    printT(T);

    return 0;
}
