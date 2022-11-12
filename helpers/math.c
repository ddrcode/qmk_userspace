#include "helpers.h"

uint16_t int_pow10(uint8_t x) {
    uint16_t res = 1;
    while(x-- > 0) res *= 10;
    return res;
}
