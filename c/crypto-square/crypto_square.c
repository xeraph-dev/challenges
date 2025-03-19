#include "crypto_square.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ciphertext(const char *input) {
    size_t input_len = strlen(input);
    size_t normalized_len = 0;
    char *normalized = calloc(input_len + 1, sizeof(char *));

    for (; *input != '\0'; input++) {
        if (isalnum(*input)) {
            normalized[normalized_len++] = tolower(*input);
        }
    }

    double len_sqrt = sqrt(normalized_len);
    size_t columns = ceil(len_sqrt);
    size_t rows = round(len_sqrt);

    char *text = calloc((columns * rows) + rows, sizeof(char *));
    size_t text_len = 0;
    size_t max_text_len = columns * rows;

    for (size_t column = {0}; column < columns; column++) {
        for (size_t row = {0}; row <= rows; row++) {
            size_t index = column + (row * columns);
            if (index >= max_text_len) {
                continue;
            }
            text[text_len++] =
                index >= normalized_len ? ' ' : normalized[index];
        }
        if (column < columns - 1) {
            text[text_len++] = ' ';
        }
    }

    free(normalized);
    return text;
}
