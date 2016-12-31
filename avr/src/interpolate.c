#include <inttypes.h>

#include "interpolate.h"

uint16_t __attribute__ ((noinline)) interpolate(uint16_t left, uint16_t right, uint8_t position, uint8_t count)
{
    volatile uint16_t l = left * (count - position);
    right = right * position;

    return ((l + right) / count);
}
