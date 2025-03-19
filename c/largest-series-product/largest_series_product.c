#include "largest_series_product.h"

#include <ctype.h>
#include <iso646.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t largest_series_product(char *digits, size_t span) {
    size_t digits_len = strlen(digits);

    if (span < 1 or span > digits_len) {
        return -1;
    }

    int64_t largest = {0};

    for (size_t i = 0; i <= digits_len - span; i++) {
        int64_t res = {1};
        for (size_t j = 0; j < span; j++) {
            char digit = digits[i + j];
            if (not isdigit(digit)) {
                return -1;
            }
            res *= digit - '0';
        }
        largest = fmax(res, largest);
    }

    return largest;
}
