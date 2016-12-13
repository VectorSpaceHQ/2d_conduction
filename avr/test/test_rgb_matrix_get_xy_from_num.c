#include <stdio.h>
#include <stdint.h>

#include "rgb_matrix.h"

int main(void)
{
    for (uint16_t i = 0; i < 768; i++) {
        uint8_t x, y;
        rgb_matrix_get_xy_from_num(i, &x, &y);
        printf("%d = (%d, %d)\n", i, x, y);
    }
}
