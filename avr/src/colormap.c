#include "colormap.h"

#include <inttypes.h>

#include "fixed.h"

void colormap_temperature_to_rgb(fixed_t temperature, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (temperature > 0x03FF) {
        temperature = 0x03FF;
    }
    
    uint16_t val = (temperature & 0x03FF) >> 1;

    if (val < 255) {
        *b = 255 - val;
        *r = 0;
    } else {
        *b = 0;
        *r = val - 255;
    }

    *g = 255 - *r - *b;
}
