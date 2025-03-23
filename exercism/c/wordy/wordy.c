#include "wordy.h"

#include <errno.h>
#include <iso646.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum operator{
    NONE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
} operator_t;

bool answer(const char *question, int *result) {
    size_t question_len = strlen(question);
    char *question_copy = calloc(question_len + 1, sizeof(char));
    strcat(question_copy, question);

    char *word = strtok(question_copy, " ");
    if (word == NULL or strcmp(word, "What") != 0) {
        return false;
    }

    word = strtok(NULL, " ");
    if (word == NULL or strcmp(word, "is") != 0) {
        return false;
    }

    bool number = true;
    operator_t op = NONE;

    *result = 0;
    for (word = strtok(NULL, " "); word != NULL; word = strtok(NULL, " ")) {
        if (number) {
            char *end;
            long n = strtol(word, &end, 10);
            if (errno == ERANGE) {
                return false;
            }

            switch (op) {
            case PLUS:
                *result += n;
                break;
            case MINUS:
                *result -= n;
                break;
            case MULTIPLY:
                *result *= n;
                break;
            case DIVIDE:
                *result /= n;
                break;
            case NONE:
                *result = n;
                break;
            }

            if (*end == '?') {
                return true;
            } else if (*end != '\0') {
                return false;
            }

            number = false;
        } else {
            if (strcmp(word, "plus") == 0) {
                op = PLUS;
            } else if (strcmp(word, "minus") == 0) {
                op = MINUS;
            } else if (strcmp(word, "multiplied") == 0) {
                word = strtok(NULL, " ");
                if (strcmp(word, "by") != 0) {
                    return false;
                }
                op = MULTIPLY;
            } else if (strcmp(word, "divided") == 0) {
                word = strtok(NULL, " ");
                if (strcmp(word, "by") != 0) {
                    return false;
                }
                op = DIVIDE;
            } else {
                return false;
            }
            number = true;
        }
    }

    free(question_copy);
    return true;
}
