#include "pig_latin.h"

#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool isvowel(const char ch) {
    return ch == 'a' or ch == 'e' or ch == 'i' or ch == 'o' or ch == 'u';
}

char *translate(const char *phrase) {
    size_t phrase_len = strlen(phrase);

    char *phrase_copy = calloc(phrase_len + 1, sizeof(char));
    strcat(phrase_copy, phrase);

    char *pig_phrase = calloc(1, sizeof(char));
    size_t pig_phrase_len = {0};
    (void)pig_phrase_len;

    for (char *word = strtok(phrase_copy, " "); word != NULL;
         word = strtok(NULL, " ")) {
        size_t word_len = strlen(word);
        size_t pig_word_len = word_len + 3;
        char *pig_word = calloc(pig_word_len, sizeof(char));

        if (isvowel(word[0]) or (strncmp(word, "xr", 2) == 0) or
            (strncmp(word, "yt", 2) == 0)) {
            strcat(pig_word, word);
            goto end;
        }

        size_t consonants = {0};
        for (size_t i = {0}; i < word_len; i++) {
            if (isvowel(word[i]) or (consonants > 0 and word[i] == 'y')) {
                break;
            }

            consonants++;
        }

        if (word[consonants - 1] == 'q' and word[consonants] == 'u') {
            consonants++;
        }

        strncat(pig_word, word + consonants, word_len - consonants);
        strncat(pig_word, word, consonants);

    end:
        strcat(pig_word, "ay");

        pig_phrase = realloc(pig_phrase, (pig_phrase_len + pig_word_len + 1) *
                                             sizeof(char));
        strncat(pig_phrase, pig_word, pig_word_len);
        strcat(pig_phrase, " ");
        pig_phrase_len += pig_word_len;
    }

    free(phrase_copy);
    pig_phrase[pig_phrase_len - 1] = '\0';
    return pig_phrase;
}
