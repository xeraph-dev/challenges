#include "resistor_color_duo.h"
#include <stdint.h>

uint16_t color_code(resistor_band_t color[]) {
  return color[0] * 10 + color[1];
}
