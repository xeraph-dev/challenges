#include "queen_attack.h"

#include <math.h>
#include <stdbool.h>

static bool position_valid(position_t pos) {
  return pos.row < 8 && pos.column < 8;
}

static bool same_row(position_t queen_1, position_t queen_2) {
  return queen_1.row == queen_2.row;
}

static bool same_column(position_t queen_1, position_t queen_2) {
  return queen_1.column == queen_2.column;
}

static bool same_position(position_t queen_1, position_t queen_2) {
  return same_row(queen_1, queen_2) && same_column(queen_1, queen_2);
}

static bool same_diagonal(position_t queen_1, position_t queen_2) {
  return fmax(queen_1.row, queen_2.row) - fmin(queen_1.row, queen_2.row) ==
         fmax(queen_1.column, queen_2.column) -
             fmin(queen_1.column, queen_2.column);
}

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
  if (!position_valid(queen_1) || !position_valid(queen_2) ||
      same_position(queen_1, queen_2))
    return INVALID_POSITION;

  if (same_row(queen_1, queen_2) || same_column(queen_1, queen_2) ||
      same_diagonal(queen_1, queen_2))
    return CAN_ATTACK;

  return CAN_NOT_ATTACK;
}
