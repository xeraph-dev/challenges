#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void fix_high(int *hour, int *minute) {
  div_t minute_div = div(*minute, 60);
  *hour = (*hour + minute_div.quot) % 24;
  *minute = minute_div.rem;
}

static void fix_low(int *hour, int *minute) {
  if (*minute < 0)
    *minute += 60, *hour -= 1;
  if (*hour < 0)
    *hour += 24;
}

clock_t clock_create(int hour, int minute) {
  fix_high(&hour, &minute);
  fix_low(&hour, &minute);

  clock_t clock = {0};
  snprintf(clock.text, MAX_STR_LEN, "%02d:%02d", hour, minute);

  return clock;
}

clock_t clock_add(clock_t clock, int minute_add) {
  int hour = atoi(strtok(clock.text, ":"));
  int minutes = atoi(strtok(NULL, ":")) + minute_add;

  return clock_create(hour, minutes);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
  int hour = atoi(strtok(clock.text, ":"));
  int minutes = atoi(strtok(NULL, ":")) - minute_subtract;

  return clock_create(hour, minutes);
}

bool clock_is_equal(clock_t a, clock_t b) {
  return strncmp(a.text, b.text, MAX_STR_LEN) == 0;
}
