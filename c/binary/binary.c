#include "binary.h"
#include <math.h>
#include <stdint.h>
#include <string.h>

int convert(const char *input) {
  uint64_t res = {0};
  uint64_t i = {strlen((input)) - 1};
  for (const char *p = input; *p != '\0'; p++, i--)
    switch (*p) {
    case '0':
      break;
    case '1':
      res += 1 * pow(2, i);
      break;
    default:
      return INVALID;
    };

  return res;
}
