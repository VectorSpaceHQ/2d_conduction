#include <stdio.h>

#include "../src/colormap.h"
#include "../src/fixed.h"

int main(void)
{
    fixed_t t = 0;

    while (t < fixed_from_real(1.1)) {
        uint8_t r, g, b;

        colormap_temperature_to_rgb(t, &r, &g, &b);

        printf("%7.3f ( %04x ) = (%02x, %02x, %02x)\n", fixed_to_float(t), t, r, g, b);

        t += fixed_from_real(0.01);
    }
}
