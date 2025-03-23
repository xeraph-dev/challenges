#include "space_age.h"

static const int64_t earthYear = 31557600;

float age(planet_t planet, int64_t seconds) {
  float years = (float)seconds / (float)earthYear;

  switch (planet) {
  case MERCURY:
    years /= 0.2408467;
    break;
  case VENUS:
    years /= 0.61519726;
    break;
  case EARTH:
    years /= 1;
    break;
  case MARS:
    years /= 1.8808158;
    break;
  case JUPITER:
    years /= 11.862615;
    break;
  case SATURN:
    years /= 29.447498;
    break;
  case URANUS:
    years /= 84.016846;
    break;
  case NEPTUNE:
    years /= 164.79132;
    break;
  default:
    years = -1;
  }

  return years;
}
