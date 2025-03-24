#pragma once

#include "house.h"
#include "zebra_puzzle.h"

#include <stdbool.h>

typedef struct houses {
    house_t houses[HOUSES];
    unsigned int rules;
} houses_t;

houses_t houses_create(void);

solution_t houses_solution(const houses_t *houses);

bool houses_is_rule_done(const houses_t *houses, unsigned int rule);
bool houses_is_completed(const houses_t *houses);
void houses_rule_done(houses_t *houses, uint8_t rule);

void houses_set_beverage(houses_t *houses, uint8_t index, beverage_t beverage);
void houses_unset_beverage(houses_t *houses, uint8_t index, beverage_t beverage);
void houses_set_color(houses_t *houses, uint8_t index, color_t color);
void houses_unset_color(houses_t *houses, uint8_t index, color_t color);
void houses_set_pet(houses_t *houses, uint8_t index, pet_t pet);
void houses_unset_pet(houses_t *houses, uint8_t index, pet_t pet);
void houses_set_hobby(houses_t *houses, uint8_t index, hobby_t hobby);
void houses_unset_hobby(houses_t *houses, uint8_t index, hobby_t hobby);
void houses_set_nationality(houses_t *houses, uint8_t index, nationality_t nationality);
void houses_unset_nationality(houses_t *houses, uint8_t index, nationality_t nationality);
