#include "rational_numbers.h"

#include <iso646.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int16_t gcd(int16_t a, int16_t b) {
    int16_t t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }

    return abs(a);
}

rational_t add(rational_t left, rational_t right) {
    return reduce((rational_t){left.numerator * right.denominator +
                                   left.denominator * right.numerator,
                               left.denominator * right.denominator});
}

rational_t subtract(rational_t left, rational_t right) {
    return reduce((rational_t){left.numerator * right.denominator -
                                   left.denominator * right.numerator,
                               left.denominator * right.denominator});
}

rational_t multiply(rational_t left, rational_t right) {
    return reduce((rational_t){left.numerator * right.numerator,
                               left.denominator * right.denominator});
}

rational_t divide(rational_t left, rational_t right) {
    return reduce((rational_t){left.numerator * right.denominator,
                               left.denominator * right.numerator});
}

rational_t absolute(rational_t value) {
    return reduce((rational_t){abs(value.numerator), abs(value.denominator)});
}

rational_t exp_rational(rational_t value, int16_t exp) {
    if (exp >= 0) {
        return reduce((rational_t){pow(value.numerator, exp),
                                   pow(value.denominator, exp)});
    } else {
        return reduce((rational_t){pow(value.denominator, -exp),
                                   pow(value.numerator, -exp)});
    }
}

float exp_real(uint16_t value, rational_t exp) {
    return pow(pow(value, exp.numerator), 1.0 / exp.denominator);
}

rational_t reduce(rational_t value) {
    int16_t gcd_value = gcd(value.numerator, value.denominator);
    value = (rational_t){value.numerator / gcd_value,
                         value.denominator / gcd_value};

    if (value.denominator < 0) {
        value.numerator *= -1;
        value.denominator *= -1;
    }

    return value;
}
