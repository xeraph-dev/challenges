#include "all_your_base.h"

#include <iso646.h>
#include <math.h>

static void swap(int8_t *a, int8_t *b) {
    *a = *a xor *b;
    *b = *a xor *b;
    *a = *a xor *b;
}

size_t rebase(int8_t digits[static DIGITS_ARRAY_SIZE], int16_t input_base,
              int16_t output_base, size_t input_len) {
    if (input_len == 0 or input_base < 2 or output_base < 2)
        return 0;

    size_t output_len = {0};
    int32_t sum = {0};

    int8_t *digits_end = {digits + input_len};
    for (int8_t *p = {digits}; p < digits_end; p++) {
        if (*p < 0 or *p >= input_base)
            return 0;
        sum += *p * pow(input_base, --input_len);
        *p = 0;
    }

    if (sum == 0)
        return 1;

    while (sum) {
        div_t res = div(sum, output_base);
        sum = res.quot;
        digits[output_len++] = res.rem;
    }

    for (int8_t *start = {digits}, *end = {digits + (output_len - 1)};
         start < end; start++, end--)
        swap(start, end);

    return output_len;
}
