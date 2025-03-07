#include "minesweeper.h"

#include <iso646.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t get_min_check(size_t v) { return (v == 0) ? 0 : (v - 1); }
static size_t get_max_check(size_t v, size_t max_v) {
    return v == max_v ? max_v : (v + 1);
}

char **annotate(const char **minefield, const size_t rows) {
    if (minefield == NULL or rows == 0) {
        return NULL;
    }

    char **annotated = calloc(rows, sizeof(char *));

    size_t max_x = {strlen(minefield[0])};
    size_t max_y = {rows};

    if (max_x > 0) {
        max_x--;
    }
    if (max_y > 0) {
        max_y--;
    }

    for (size_t y = {0}; y <= max_y; y++) {
        annotated[y] = calloc(max_x + 2, sizeof(char));
        for (size_t x = {0}; x <= max_x; x++) {
            if (minefield[y][x] == '\0') {
                break;
            }
            if (minefield[y][x] == '*') {
                annotated[y][x] = '*';
                continue;
            }

            size_t min_check_x = get_min_check(x);
            size_t max_check_x = get_max_check(x, max_x);
            size_t min_check_y = get_min_check(y);
            size_t max_check_y = get_max_check(y, max_y);
            uint8_t value = {0};

            for (size_t cy = min_check_y; cy <= max_check_y; cy++) {
                for (size_t cx = min_check_x; cx <= max_check_x; cx++) {
                    if (minefield[cy][cx] == '*') {
                        value++;
                    }
                }
            }

            if (value == 0) {
                annotated[y][x] = ' ';
                continue;
            }

            char value_str[4];
            snprintf(value_str, 4, "%u", value);
            annotated[y][x] = *value_str;
        }
    }

    return annotated;
}

void free_annotation(char **annotation) { (void)annotation; }
