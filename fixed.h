#include <stdint.h>

typedef int16_t fixed_t;
typedef int32_t dfixed_t;

#define FIXED_BITS  (10)

#define fixed_from_real(x)  ((fixed_t)((x) * (((fixed_t)1 << FIXED_BITS) + ((x) > 0 ? 0.5 : -0.5))))
#define fixed_from_int(x)   ((fixed_t)(x) << FIXED_BITS)
#define fixed_to_int(x)     ((x) >> FIXED_BITS)
#define fixed_mul(x,y)      ((fixed_t)(((dfixed_t)(x) * (dfixed_t)(y)) >> FIXED_BITS))
#define fixed_div(x,y)      ((fixed_t)(((dfixed_t)(x) << FIXED_BITS) / (dfixed_t)(y)))
#define fixed_to_float(x)   ((float)(((x) >> FIXED_BITS) + ((float)((x) & 0x03FF) / 1024.0)))
//#define fixed_to_float(x)   ((float)(256.0))
