#include "etl.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *a, const void *b) {
    return ((const new_map *)a)->key - ((const new_map *)b)->key;
}

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
    size_t output_len = {0};

    const legacy_map *input_end = {input + input_len};
    for (const legacy_map *ip = {input}; ip < input_end; ip++) {
        output_len += strlen(ip->keys);
    }

    *output = calloc(output_len, sizeof(new_map));

    size_t output_idx = {0};
    for (const legacy_map *ip = {input}; ip < input_end; ip++) {
        for (const char *ch = {ip->keys}; *ch != '\0'; ch++) {
            (*output)[output_idx++] = (new_map){tolower(*ch), ip->value};
        }
    }

    qsort(*output, output_len, sizeof(new_map), compare);
    return output_len;
}
