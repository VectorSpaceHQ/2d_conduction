#ifndef TIMER_H
#define TIMER_H

#include <inttypes.h>

#define TIMER_TICKS_PER_SEC (F_CPU / 1024)

void timer_start(void);
void timer_clear(void);
uint16_t timer_get_ticks(void);

#endif // TIMER_H

