#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t iforward = -1;
    uint8_t kforward = 1;
    uint8_t column = 0;
    uint8_t row = 0;
    uint16_t count = 0;

    for (uint8_t k = 0; k < 12; k++) {
        for (uint8_t j = 0; j < 8; j++) {
            iforward = iforward * -1;
            if (iforward > 0){
                for (uint8_t i = 0; i < 8; i++) {
                    uint8_t x = i + (8 * column);
                    uint8_t y = j + (8 * row);

                    printf("%d = (%d, %d)\n", count, x, y);
                    count++;
                }
            }
            else{
                for (uint8_t i = 7; i >= 0; i--) {
                    uint8_t x = i + (8 * column);
                    uint8_t y = j + (8 * row);

                    printf("%d = (%d, %d)\n", count, x, y);
                    count++;
                }
            }
        }
        if ((k+1) % 4 == 0){
            kforward = kforward * -1;
            row += 1;
            column = column - kforward;
        }
        column = column + kforward;
    }

    return 0;
}
