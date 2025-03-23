#include "anagram.h"

#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *a, const void *b) {
    char *ach = (char *)a;
    char *bch = (char *)b;
    *ach = tolower(*ach);
    *bch = tolower(*bch);
    return strcmp(ach, bch);
}

static bool equal(const char *subject, const char *candidate) {
    while (*subject != '\0' and *candidate != '\0') {
        if (tolower(*subject++) != tolower(*candidate++)) {
            return false;
        }
    }
    return *subject == '\0' and *candidate == '\0';
}

static enum anagram_status are_anagrams(const char *subject,
                                        const char *subject_sorted,
                                        const char *candidate) {
    size_t candidate_len = strlen(candidate);
    char *candidate_sorted = calloc(candidate_len, sizeof(char));
    strcpy(candidate_sorted, candidate);
    qsort(candidate_sorted, candidate_len, sizeof(char), compare);

    return not equal(subject, candidate) and
                   equal(subject_sorted, candidate_sorted)
               ? IS_ANAGRAM
               : NOT_ANAGRAM;
}

void find_anagrams(const char *subject, struct candidates *candidates) {
    size_t subject_len = strlen(subject);
    char *subject_sorted = calloc(subject_len, sizeof(char));
    strcpy(subject_sorted, subject);
    qsort(subject_sorted, subject_len, sizeof(char), compare);

    const struct candidate *const candidates_end = {candidates->candidate +
                                                    candidates->count};
    for (struct candidate *candidate = {candidates->candidate};
         candidate < candidates_end; candidate++) {
        candidate->is_anagram =
            are_anagrams(subject, subject_sorted, candidate->word);
    }
}
