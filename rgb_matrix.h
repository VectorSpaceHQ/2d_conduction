#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H

#include <inttypes.h>

void rgb_matrix_start_frame(void);
void rgb_matrix_send_pixel(uint8_t r, uint8_t g, uint8_t b);
void rgb_matrix_end_frame(void);

#endif // RGB_MATRIX_H
