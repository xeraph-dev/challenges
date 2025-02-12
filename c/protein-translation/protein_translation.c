#include "protein_translation.h"

proteins_t proteins(const char *const rna) {
  proteins_t p = {.valid = true};
  proteins_t invalid = {.valid = false};

  for (const char *rnap = {rna}; *rnap != '\0';) {
    switch (*(rnap++)) {
    case 'A':
      switch (*(rnap++)) {
      case 'U':
        switch (*(rnap++)) {
        case 'G':
          p.proteins[p.count++] = Methionine;
          break;
        default:
          return invalid;
        }
        break;
      default:
        return invalid;
      }
      break;
    case 'U':
      switch (*(rnap++)) {
      case 'A':
        switch (*(rnap++)) {
        case 'A':
        case 'G':
          return p;
        case 'C':
        case 'U':
          p.proteins[p.count++] = Tyrosine;
          break;
        default:
          return invalid;
        }
        break;
      case 'C':
        switch (*(rnap++)) {
        case 'A':
        case 'C':
        case 'G':
        case 'U':
          p.proteins[p.count++] = Serine;
          break;
        default:
          return invalid;
        }
        break;
      case 'G':
        switch (*(rnap++)) {
        case 'A':
          return p;
        case 'G':
          p.proteins[p.count++] = Tryptophan;
          break;
        case 'C':
        case 'U':
          p.proteins[p.count++] = Cysteine;
          break;
        default:
          return invalid;
        }
        break;
      case 'U':
        switch (*(rnap++)) {
        case 'A':
        case 'G':
          p.proteins[p.count++] = Leucine;
          break;
        case 'C':
        case 'U':
          p.proteins[p.count++] = Phenylalanine;
          break;
        default:
          return invalid;
        }
        break;
      default:
        return invalid;
      }
      break;
    default:
      return invalid;
    }
  }

  return p;
}
