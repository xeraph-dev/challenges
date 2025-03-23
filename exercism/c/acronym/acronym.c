#include "acronym.h"

#include <ctype.h>
#include <iso646.h>
#include <stdlib.h>
#include <string.h>

static void drop_separators(const char **input) {
    while (**input != '\0' and
           (**input == ' ' or **input == '-' or **input == '_')) {
        (*input)++;
    }
}

static void drop_word(const char **input) {
    while (**input != '\0' and **input != ' ' and **input != '-') {
        (*input)++;
    }
}

char *abbreviate(const char *phrase) {
    if (phrase == NULL)
        return NULL;

    size_t res_len = {0};
    char *res = calloc(res_len, sizeof(char));
    while (*phrase != '\0') {
        drop_separators(&phrase);
        res = realloc(res, res_len + 1);
        res[res_len++] = toupper(*phrase);
        drop_word(&phrase);
    }

    if (res_len == 0) {
        free(res);
        return NULL;
    }

    return res;
}
