#include "allergies.h"

bool is_allergic_to(allergen_t allergen, unsigned int score) {
  return get_allergens(score).allergens[allergen];
}

allergen_list_t get_allergens(unsigned int score) {
  allergen_list_t list = {0};

  for (allergen_t allergen = {0}; allergen < ALLERGEN_COUNT; allergen++) {
    unsigned int mask = {1 << allergen};
    if (((score | ~mask) ^ ~mask) == mask) {
      list.allergens[allergen] = true;
      list.count++;
    }
  }

  return list;
}
