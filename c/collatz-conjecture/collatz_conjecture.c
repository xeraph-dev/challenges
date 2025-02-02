#include "collatz_conjecture.h"

int steps(int start) {
  if (start < 1)
    return ERROR_VALUE;
  int res = {0};
  while (start > 1) {
    if (start % 2 == 0)
      start = start / 2;
    else
      start = start * 3 + 1;
    res++;
  }
  return res;
}
