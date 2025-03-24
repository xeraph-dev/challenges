#pragma once

#include <stdbool.h>
#include <stdint.h>

#define HOUSES 5

#define foreach_house for (uint8_t i = {0}; i < HOUSES; i++)

typedef enum beverage { BEVERAGE_UNSET, COFFEE, MILK, TEA, JUICE, WATER } beverage_t;
typedef enum color { COLOR_UNSET, RED, BLUE, YELLOW, GREEN, IVORY } color_t;
typedef enum pet { PET_UNSET, SNAIL, FOX, HORSE, DOG, ZEBRA } pet_t;
typedef enum hobby { HOBBY_UNSET, PAINT, DANCE, READ, FOOTBALL, CHESS } hobby_t;
typedef enum nationality { NATIONALITY_UNSET, SPANIARD, ENGLISHMAN, UKRAINIAN, JAPANESE, NORWEGIAN } nationality_t;

char *beverage_string(beverage_t beverage);
char *color_string(color_t color);
char *pet_string(pet_t pet);
char *hobby_string(hobby_t hobby);
char *nationality_string(nationality_t nationality);

typedef struct house {
    beverage_t beverage[HOUSES];
    color_t color[HOUSES];
    pet_t pet[HOUSES];
    hobby_t hobby[HOUSES];
    nationality_t nationality[HOUSES];

    uint8_t beverage_len;
    uint8_t color_len;
    uint8_t pet_len;
    uint8_t hobby_len;
    uint8_t nationality_len;
} house_t;

house_t house_create(void);

bool house_is_first(uint8_t index);
bool house_is_last(uint8_t index);

bool house_hasnot_beverage(const house_t *house, beverage_t beverage);
bool house_has_beverage(const house_t *house, beverage_t beverage);
bool house_isset_beverage(const house_t *house);
void house_set_beverage(house_t *house, beverage_t beverage);
void house_unset_beverage(house_t *house, beverage_t beverage);

bool house_hasnot_color(const house_t *house, color_t color);
bool house_has_color(const house_t *house, color_t color);
bool house_isset_color(const house_t *house);
void house_set_color(house_t *house, color_t color);
void house_unset_color(house_t *house, color_t color);

bool house_hasnot_pet(const house_t *house, pet_t pet);
bool house_has_pet(const house_t *house, pet_t pet);
bool house_isset_pet(const house_t *house);
void house_set_pet(house_t *house, pet_t pet);
void house_unset_pet(house_t *house, pet_t pet);

bool house_hasnot_hobby(const house_t *house, hobby_t hobby);
bool house_has_hobby(const house_t *house, hobby_t hobby);
bool house_isset_hobby(const house_t *house);
void house_set_hobby(house_t *house, hobby_t hobby);
void house_unset_hobby(house_t *house, hobby_t hobby);

bool house_hasnot_nationality(const house_t *house, nationality_t nationality);
bool house_has_nationality(const house_t *house, nationality_t nationality);
bool house_isset_nationality(const house_t *house);
void house_set_nationality(house_t *house, nationality_t nationality);
void house_unset_nationality(house_t *house, nationality_t nationality);
