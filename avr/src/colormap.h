#ifndef COLORMAP_H
#define COLORMAP_H

#include <inttypes.h>

#include "fixed.h"

void colormap_temperature_to_rgb(fixed_t temperature, uint8_t *r, uint8_t *g, uint8_t *b);

#endif //COLORMAP_H

