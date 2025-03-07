#include "run_length_encoding.h"

#include <ctype.h>
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

static size_t number_len(size_t n) {
    size_t len = {1};
    while (n >= 10) {
        n /= 10;
        len++;
    }
    return len;
}

char *encode(const char *text) {
    size_t data_len = 0;
    char *data = calloc(1, sizeof(char *));

    if (*text == '\0') {
        return data;
    }

    size_t repeat = {1};
    char letter = {*text};
    for (const char *ch = {text + 1};; ch++) {
        if (*ch == letter) {
            repeat++;
            continue;
        }

        if (repeat == 1) {
            data = realloc(data, data_len + (sizeof(char *)));
            snprintf(data + data_len, 2, "%c", letter);
            data_len++;
        } else {
            size_t repeat_len = number_len(repeat);
            data =
                realloc(data, data_len + (sizeof(char *) * (repeat_len + 1)));
            snprintf(data + data_len, repeat_len + 2, "%zu%c", repeat, letter);
            data_len += repeat_len + 1;
        }
        repeat = 1;
        letter = *ch;

        if (*ch == '\0') {
            break;
        }
    }

    return data;
}

char *decode(const char *data) {
    size_t text_len = 0;
    char *text = calloc(1, sizeof(char *));

    if (*data == '\0') {
        return text;
    }

    for (const char *ch = {data};; ch++) {
        size_t repeat = {0};
        if (isdigit(*ch)) {
            while (isdigit(*ch)) {
                repeat *= 10;
                repeat += *ch - '0';
                ch++;
            }
        } else {
            repeat = 1;
        }

        text = realloc(text, text_len + (sizeof(char *) * repeat));
        for (; repeat > 0; repeat--) {
            text[text_len++] = *ch;
        }

        if (*ch == '\0') {
            break;
        }
    }

    return text;
}
