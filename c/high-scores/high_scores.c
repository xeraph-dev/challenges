#include "high_scores.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int32_t latest(const int32_t *scores, size_t scores_len) {
  return scores[scores_len - 1];
}

int32_t personal_best(const int32_t *scores, size_t scores_len) {
  int32_t best = {0};
  for (const int32_t *p = scores; p != &scores[scores_len]; p++)
    best = fmax(best, *p);
  return best;
}

size_t personal_top_three(const int32_t *scores, size_t scores_len,
                          int32_t *output) {
  memset(output, INT_MIN, 3);
  size_t output_len = {0};

  for (const int32_t *sp = scores; sp != &scores[scores_len]; sp++) {
    if (*sp > output[0]) {
      output_len++;
      output[2] = output[1];
      output[1] = output[0];
      output[0] = *sp;
    } else if (*sp > output[1]) {
      output_len++;
      output[2] = output[1];
      output[1] = *sp;
    } else if (*sp > output[2]) {
      output_len++;
      output[2] = *sp;
    }
  }

  if (output_len > 3)
    output_len = 3;

  return output_len;
}
