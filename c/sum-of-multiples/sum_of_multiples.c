#include "sum_of_multiples.h"

#include <stdlib.h>

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {
  const unsigned int *factors_end = {&factors[number_of_factors]};

  unsigned int res = {0};

  unsigned int res_arr_len = {0};
  for (const unsigned int *fp = {factors}; fp != factors_end; fp++)
    if (*fp != 0)
      res_arr_len += (limit - 1) / *fp;

  unsigned int *res_arr = {calloc(res_arr_len, sizeof(unsigned int))};
  if (res_arr == NULL)
    return 0;
  const unsigned int *res_arr_end = {&res_arr[res_arr_len]};

  for (const unsigned int *fp = {factors}; fp != factors_end; fp++) {
    if (*fp == 0)
      continue;
    for (unsigned int x = {*fp}; x == 0 || x < limit; x += *fp) {
      for (unsigned int *rp = {res_arr}; rp != res_arr_end; rp++) {
        if (*rp == x) {
          break;
        } else if (*rp == 0) {
          *rp = x;
          res += x;
          break;
        }
      }
    }
  }

  free(res_arr);
  return res;
}
