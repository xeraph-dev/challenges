#include "rotational_cipher.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *rotate(const char *text, int shift_key) {
  char *res = calloc(strlen(text), sizeof(char));
  strcpy(res, text);

  for (char *p = {res}; *p != '\0'; p++) {
    if (isalpha(*p)) {
      const int min = islower(*p) ? 'a' : 'A';
      *p = ((*p - min + shift_key) % 26) + min;
    }
  }

  return res;
}
