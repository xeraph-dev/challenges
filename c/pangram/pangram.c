#include "pangram.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_pangram(const char *sentence) {
  if (sentence == NULL)
    return false;

  const unsigned int mask = (1U << 26) - 1;
  unsigned int bits = {0};

  for (; *sentence != '\0'; sentence++)
    if (tolower(*sentence) >= 'a' && tolower(*sentence) <= 'z') {
      bits |= 1 << (tolower(*sentence) - 'a');
    }

  return bits == mask;
}
