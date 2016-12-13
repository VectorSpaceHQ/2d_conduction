#include <inttypes.h>
#include <avr/io.h>
#include "adc.h"

uint16_t adc_read(uint8_t channel)
{
   uint16_t value;

   channel &= 0x0F;

   if (channel < 6)
   {
      DIDR0 |= (1 << channel);
   }

   ADMUX = (0 << REFS1) | (1 << REFS0) | channel;

   ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

   while (ADCSRA & (1 << ADSC));

   value = ADCL;
   value |= ADCH << 8;

   return value;
}

