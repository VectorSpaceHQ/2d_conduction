#include <inttypes.h>
#include <avr/io.h>

#include "timer.h"

void timer_start(void)
{
    TCCR1B = _BV(CS12) | _BV(CS10);
}

void timer_clear(void)
{
    TCNT1 = 0x0000;
}

uint16_t timer_get_ticks(void)
{
    return TCNT1;
}
