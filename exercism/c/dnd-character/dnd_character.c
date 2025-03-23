#include "dnd_character.h"
#include <math.h>
#include <stdlib.h>

static int dice(void) { return (rand() % 6) + 1; }

int ability(void) {
  int value = {0};
  int min = {dice()};

  for (int i = {0}; i < 3; i++) {
    int r = {dice()};
    value += fmax(r, min);
    min = fmin(r, min);
  }

  return value;
}

int modifier(int score) { return (int)floor(((double)score - 10) / 2); }

dnd_character_t make_dnd_character(void) {
  int constitution = ability();
  return (dnd_character_t){
      .strength = ability(),
      .dexterity = ability(),
      .constitution = constitution,
      .intelligence = ability(),
      .wisdom = ability(),
      .charisma = ability(),
      .hitpoints = 10 + modifier(constitution),
  };
}
