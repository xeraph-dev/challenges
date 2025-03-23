#include "square_root.h"
#include <stdio.h>

uint16_t square_root(uint16_t num) {
  if (num == 0)
    return 0;
  if (num == 1)
    return 1;

  uint16_t min = {0}, max = {num}, pivot = {0};

  while (min + 1 < max) {
    pivot = (max - min) / 2 + min;
    uint32_t square = pivot * pivot;
    if (square == num) {
      break;
    } else if (square > num) {
      max = pivot;
    } else {
      min = pivot;
    }
  }

  return pivot;
}
