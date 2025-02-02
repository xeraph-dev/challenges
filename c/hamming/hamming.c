#include "hamming.h"

int compute(const char *lhs, const char *rhs) {
  int diff = {0};
  const char *lp, *rp;
  for (lp = lhs, rp = rhs; *lp != '\0' && *rhs != '\0'; lp++, rp++)
    if (*lp != *rp)
      diff++;
  if ((*lp == '\0') ^ (*rp == '\0'))
    diff = -1;
  return diff;
}
