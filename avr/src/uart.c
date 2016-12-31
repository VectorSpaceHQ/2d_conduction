#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include "uart.h"

static int uart_putchar(char c, FILE *stream);
static int uart_getchar(FILE *stream);

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE uart_stdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ );

void uart_init(uint16_t baud)
{
   UBRR0H = (uint8_t) (baud >> 8);
   UBRR0L = (uint8_t) (baud);

   UCSR0B = (1 << RXEN0) | (1 << TXEN0);
   UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

   stdout = &uart_stdout;
   stdin =  &uart_stdin;
}

static int uart_putchar(char c, FILE *stream)
{
   while ( !(UCSR0A & (1 << UDRE0)) );

   UDR0 = c;

   return 0;
}

static int uart_getchar(FILE *stream)
{
   int c;

   while ( !(UCSR0A & (1 << RXC0)) );

   c = UDR0;

   uart_putchar(c, stream);

   return c;
}
