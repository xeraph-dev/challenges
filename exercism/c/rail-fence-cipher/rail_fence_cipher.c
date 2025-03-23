#include "rail_fence_cipher.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char **fence_create(size_t text_len, size_t rails) {
    char **fence = calloc(rails, sizeof(char *));

    for (size_t y = {0}; y < rails; y++) {
        fence[y] = calloc(text_len + 1, sizeof(char));
        for (size_t x = {0}; x < text_len; x++) {
            fence[y][x] = '.';
        }
    }

    bool asc = true;
    for (size_t y = {0}, x = {0}; x < text_len; x++) {
        fence[y][x] = '?';
        if (y == (rails - 1)) {
            asc = false;
        } else if (y == 0) {
            asc = true;
        }
        if (asc) {
            y++;
        } else {
            y--;
        }
    }

    return fence;
}

static void fence_free(char **fence, size_t rails) {
    for (size_t i = {0}; i < rails; i++) {
        free(fence[i]);
    }
    free(fence);
}

char *encode(char *text, size_t rails) {
    size_t text_len = strlen(text);
    size_t cipher_text_len = {0};
    char *cipher_text = calloc(text_len + 1, sizeof(char));

    char **fence = fence_create(text_len, rails);

    for (size_t x = {0}; x < text_len; x++) {
        for (size_t y = {0}; y < rails; y++) {
            if (fence[y][x] == '?') {
                fence[y][x] = text[x];
            }
        }
    }

    for (size_t y = {0}; y < rails; y++) {
        for (size_t x = {0}; x < text_len; x++) {
            if (fence[y][x] != '.') {
                cipher_text[cipher_text_len++] = fence[y][x];
            }
        }
    }

    fence_free(fence, rails);

    cipher_text[cipher_text_len] = '\0';
    return cipher_text;
}

char *decode(char *ciphertext, size_t rails) {
    size_t ciphertext_len = strlen(ciphertext);
    size_t text_len = {0};
    char *text = calloc(ciphertext_len + 1, sizeof(char));

    char **fence = fence_create(ciphertext_len, rails);

    size_t len = {0};
    for (size_t y = {0}; y < rails; y++) {
        for (size_t x = {0}; x < ciphertext_len; x++) {
            if (fence[y][x] == '?') {
                fence[y][x] = ciphertext[len++];
            }
        }
    }

    for (size_t x = {0}; x < ciphertext_len; x++) {
        for (size_t y = {0}; y < rails; y++) {
            if (fence[y][x] != '.') {
                text[text_len++] = fence[y][x];
            }
        }
    }

    fence_free(fence, rails);

    text[text_len] = '\0';
    return text;
}
