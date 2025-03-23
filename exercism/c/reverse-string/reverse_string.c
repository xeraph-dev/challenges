#include "reverse_string.h"
#include <stdlib.h>
#include <string.h>

char *reverse(const char *value) {
  const size_t value_len = strlen(value);

  char *res = {calloc(value_len, sizeof(char))};
  char *res_end = res + value_len;

  while (res < res_end)
    *(--res_end) = *(value++);

  return res;
}
