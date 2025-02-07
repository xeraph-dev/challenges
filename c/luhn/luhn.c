#include "luhn.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool luhn(const char *num) {
  if (num == NULL)
    return false;

  size_t len = {0};
  for (const char *p = {num}; *p != '\0'; p++)
    if (isspace(*p))
      continue;
    else if (!isdigit(*p))
      return false;
    else
      len++;
  ;

  if (len <= 1)
    return false;

  size_t sum = {0};

  for (const char *p = {num}; *p != '\0'; p++) {
    if (isspace(*p))
      continue;

    uint8_t digit = *p - '0';
    if (len-- % 2 == 0)
      digit *= 2;
    if (digit > 9)
      digit -= 9;

    sum += digit;
  }

  printf("- sum %zu -", sum);

  return sum % 10 == 0;
}
