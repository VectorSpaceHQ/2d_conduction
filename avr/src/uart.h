#ifndef UART_H
#define UART_H

#include <inttypes.h>

#define BAUD(x) ((F_CPU / (16UL * (x))) - 1)

void uart_init(uint16_t baud);

#endif // UART_H
