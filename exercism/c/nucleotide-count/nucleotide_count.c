#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>

char *count(const char *dna_strand) {
  size_t a = {0}, c = {0}, g = {0}, t = {0};

  char *res = calloc(100, sizeof(char));

  for (const char *p = {dna_strand}; *p != '\0'; p++)
    switch (*p) {
    case 'A':
      a++;
      break;
    case 'C':
      c++;
      break;
    case 'G':
      g++;
      break;
    case 'T':
      t++;
      break;
    default:
      return res;
    }

  sprintf(res, "A:%zu C:%zu G:%zu T:%zu", a, c, g, t);
  return res;
}
