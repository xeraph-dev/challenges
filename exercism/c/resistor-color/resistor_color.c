#include "resistor_color.h"
#include <stdint.h>

uint16_t color_code(resistor_band_t color) { return (uint16_t)color; }

resistor_band_t *colors(void) {
  static resistor_band_t res[] = {BLACK, BROWN, RED,    ORANGE, YELLOW,
                                  GREEN, BLUE,  VIOLET, GREY,   WHITE};
  return res;
}
