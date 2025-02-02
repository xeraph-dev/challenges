#include "grains.h"
#include <math.h>
#include <stdint.h>

uint64_t square(uint8_t index) {
  if (index > 64)
    return 0;
  return pow(2, index - 1);
}
uint64_t total(void) {
  uint64_t res = {0};
  for (uint8_t i = {1}; i <= 64; i++) {
    res += square(i);
  }
  return res;
}
