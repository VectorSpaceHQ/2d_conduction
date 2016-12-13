#include <inttypes.h>
#include <avr/io.h>
#include "spi.h"

void spi_master_init(void)
{
   if ( !(DDRB & (1 << PB2)) )
   {
      PORTB |= (1 << PB2);
   }

   DDRB |= (1 << PB5) | (1 << PB3);
   SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_transfer(uint8_t tx)
{
   SPDR = tx;

   while ( !(SPSR & (1 << SPIF)) );

   return SPDR;
}
