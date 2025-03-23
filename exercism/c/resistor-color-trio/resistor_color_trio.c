#include "resistor_color_trio.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

resistor_value_t color_code(resistor_band_t *bands) {
  resistor_value_t value = {0};
  value.value = (bands[0] * 10 + bands[1]) * pow(10, bands[2]);
  while (value.value >= 1000) {
    value.value /= 1000;
    value.unit += 1;
  }
  return value;
}
