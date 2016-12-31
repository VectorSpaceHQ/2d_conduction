#include <inttypes.h>

#include "interpolate.h"

uint16_t interpolate(uint16_t left, uint16_t right, uint8_t position, uint8_t count)
{
    left = left * (count - position);
    right = right * position;

    return ((left + right) / count);
}
