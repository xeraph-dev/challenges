#ifndef RATIONAL_NUMBERS_H
#define RATIONAL_NUMBERS_H

#include <stdint.h>

typedef struct {
    int16_t numerator;
    int16_t denominator;
} rational_t;

rational_t add(rational_t left, rational_t right);
rational_t subtract(rational_t left, rational_t right);
rational_t multiply(rational_t left, rational_t right);
rational_t divide(rational_t left, rational_t right);
rational_t absolute(rational_t value);
rational_t exp_rational(rational_t value, int16_t exp);
float exp_real(uint16_t value, rational_t exp);
rational_t reduce(rational_t value);

#endif
