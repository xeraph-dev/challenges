#include "diamond.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char **make_diamond(const char letter) {
    size_t diamond_len = {((letter - 'A') * 2) + 1};
    char **diamond = calloc(diamond_len, sizeof(char *));
    char **diamond_end = diamond + diamond_len;

    char curr_letter = {'A'};
    int inc = 1;
    for (char **row = {diamond}; row < diamond_end; row++, curr_letter += inc) {
        *row = calloc(diamond_len + 1, sizeof(char));

        int outside_padding = {letter - curr_letter};
        int inside_padding = {(diamond_len - 2) - (outside_padding * 2)};
        if (curr_letter == 'A') {
            snprintf(*row, diamond_len + 1, "%*s%c%*s", outside_padding, "",
                     curr_letter, outside_padding, "");
        } else {
            snprintf(*row, diamond_len + 1, "%*s%c%*s%c%*s", outside_padding,
                     "", curr_letter, inside_padding, "", curr_letter,
                     outside_padding, "");
        }

        if (curr_letter == letter) {
            inc = -1;
        }
    }

    return diamond;
}

void free_diamond(char **diamond) { (void)diamond; }
