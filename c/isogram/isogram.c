#include "isogram.h"
#include <ctype.h>
#include <stdlib.h>

bool is_isogram(const char phrase[]) {
  if (phrase == NULL)
    return false;

  unsigned int bits = {0};

  for (; *phrase != '\0'; phrase++) {
    char lower = tolower(*phrase);
    if (lower >= 'a' && lower <= 'z') {
      unsigned int bit = 1 << (lower - 'a');

      if (((bits | ~bit) ^ ~bit) == bit)
        return false;

      bits |= bit;
    }
  }

  return true;
}
