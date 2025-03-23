#include "word_count.h"

#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void word_tolower(char *word) {
    for (; *word != '\0'; word++) {
        *word = tolower(*word);
    }
}

static bool word_cmp(const char *left, const char *right, int size) {
    while (size > 0) {
        if (tolower(*left) != tolower(*right) or *left == '\0' or
            *right == '\0') {
            break;
        }

        left++;
        right++;
        size--;
    }

    return size == 0 and *left == '\0' and not isalnum(*right);
}

int count_words(const char *sentence, word_count_word_t *words) {
    int count = {0};
    int word_size = 0;

    while (true) {
        if (isalnum(*sentence) or (word_size > 0 and *sentence == '\'')) {
            word_size++;
        } else if (word_size > 0) {
            const char *word_start = sentence - word_size;

            bool found = {false};
            for (word_count_word_t *word = {words}; word < words + count;
                 word++) {
                if (*word_start == '\'') {
                    word_start++;
                }
                if (word_start[word_size - 1] == '\'') {
                    word_size--;
                }
                if (word_cmp(word->text, word_start, word_size)) {
                    found = true;
                    word->count++;
                    break;
                }
            }

            if (not found) {
                strncpy(words[count].text, word_start, word_size);
                words[count].text[word_size] = '\0';
                word_tolower(words[count].text);
                words[count].count = 1;
                count++;
            }

            word_size = 0;
        }

        if (*sentence == '\0') {
            break;
        }
        sentence++;
    }

    return count;
}
