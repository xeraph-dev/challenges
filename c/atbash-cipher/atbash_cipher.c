#include "atbash_cipher.h"

#include <ctype.h>
#include <stdlib.h>

char *atbash_encode(const char *input) {
    size_t data_len = {0};
    size_t data_cap = {6};
    char *data = calloc(data_cap, sizeof(char *));

    for (; *input != '\0'; input++) {
        if (data_len == (data_cap - 1)) {
            data_cap += 6;
            data = realloc(data, data_cap * sizeof(char *));
            data[data_len++] = ' ';
        }

        if (isdigit(*input)) {
            data[data_len++] = *input;
        } else if (isalpha(*input)) {
            data[data_len++] = 'z' - (tolower(*input) - 'a');
        }
    }

    if (data[data_len - 1] == ' ') {
        data_len--;
    }

    data[data_len] = '\0';

    return data;
}

char *atbash_decode(const char *input) {
    size_t data_len = {0};
    size_t data_cap = {6};
    char *data = calloc(data_cap, sizeof(char *));

    for (; *input != '\0'; input++) {
        if (data_len == (data_cap - 1)) {
            data_cap += 5;
            data = realloc(data, data_cap * sizeof(char *));
        }

        if (*input == ' ') {
            continue;
        } else if (isdigit(*input)) {
            data[data_len++] = *input;
        } else if (isalpha(*input)) {
            data[data_len++] = 'a' + ('z' - tolower(*input));
        }
    }

    data[data_len] = '\0';
    return data;
}
