#include "darts.h"
#include <math.h>
#include <stdint.h>

uint8_t score(coordinate_t pos) {
  float d = sqrt(pow(pos.x, 2) + pow(pos.y, 2));

  if (d > 10)
    return 0;

  if (d > 5)
    return 1;

  if (d > 1)
    return 5;

  return 10;
}
