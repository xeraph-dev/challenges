#include "series.h"

#include <iso646.h>
#include <stdlib.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length) {
    slices_t res = {0};

    if (substring_length == 0) {
        return res;
    }

    size_t input_len = {strlen(input_text)};
    for (char *ch = {input_text}; *ch != '\0'; ch++, input_len--) {
        if (input_len < substring_length) {
            break;
        }

        char *str = calloc(substring_length + 1, sizeof(char));
        strncpy(str, ch, substring_length);
        str[substring_length] = '\0';

        res.substring =
            realloc(res.substring, (res.substring_count + 1) * sizeof(char *));
        res.substring[res.substring_count] = str;
        res.substring_count++;
    }

    return res;
}
