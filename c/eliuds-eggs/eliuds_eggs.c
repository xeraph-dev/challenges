#include "eliuds_eggs.h"
#include <stdlib.h>

unsigned int egg_count(unsigned int count) {
  unsigned int eggs = {0};

  for (; count > 0;) {
    div_t count_d = div(count, 2);
    eggs += count_d.rem;
    count = count_d.quot;
  }

  return eggs;
}
