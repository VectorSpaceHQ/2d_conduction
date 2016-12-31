#include <inttypes.h>
#include <stdio.h>

#include "../src/interpolate.h"

int main(void) 
{
    for (int i = 0; i < 16; i++) {
        printf("%d: %d\n", i, interpolate(0, 1023, i, 16));
    }
}
