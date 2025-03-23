#include "sieve.h"

#include <math.h>
#include <stdint.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes) {
  (void)primes;
  size_t list_len = {limit - 1};
  int64_t list[list_len];
  const int64_t *list_end = list + list_len;

  size_t num = {2};
  for (int64_t *lp = {list}; lp != list_end; lp++, num++)
    *lp = num;

  size_t primes_len = {0};
  for (int64_t *lp = {list}; lp != list_end; lp++) {
    if (*lp > 0) {
      primes[primes_len++] = *lp;
      for (int64_t *ilp = {lp + *lp}; ilp < list_end; ilp += *lp) {
        if (*ilp > 0) {
          *ilp *= -1;
        }
      }
    }
  }

  return fmin(primes_len, max_primes);
}
