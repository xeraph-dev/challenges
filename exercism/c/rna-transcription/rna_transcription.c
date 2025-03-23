#include "rna_transcription.h"
#include <stdlib.h>
#include <string.h>

char *to_rna(const char *dna) {
  char *rna = malloc(strlen(dna));

  char *rna_p = rna;
  for (const char *dna_p = dna; *dna_p != '\0'; dna_p++, rna_p++)
    switch (*dna_p) {
    case 'G':
      *rna_p = 'C';
      break;
    case 'C':
      *rna_p = 'G';
      break;
    case 'T':
      *rna_p = 'A';
      break;
    case 'A':
      *rna_p = 'U';
      break;
    }

  return rna;
}
