#include "houses.h"
#include "house.h"

houses_t houses_create(void) {
    return (houses_t){
        .houses = {house_create(), house_create(), house_create(), house_create(), house_create()},
        .rules = 1,
    };
}

solution_t houses_solution(const houses_t *houses) {
    solution_t solution = {0};

    foreach_house {
        if (houses->houses[i].beverage[0] == WATER) {
            solution.drinks_water = nationality_string(houses->houses[i].nationality[0]);
        }
        if (houses->houses[i].pet[0] == ZEBRA) {
            solution.owns_zebra = nationality_string(houses->houses[i].nationality[0]);
        }
    }

    return solution;
}

bool houses_is_rule_done(const houses_t *houses, unsigned int rule) {
    unsigned int bit = 1 << (rule - 1);
    return ((houses->rules | ~bit) ^ ~bit) == bit;
}

bool houses_is_completed(const houses_t *houses) { return houses->rules == 32767; }

void houses_rule_done(houses_t *houses, uint8_t rule) { houses->rules |= 1 << (rule - 1); }

void houses_set_beverage(houses_t *houses, uint8_t index, beverage_t beverage) {
    foreach_house {
        if (i == index) {
            house_set_beverage(&houses->houses[i], beverage);
        } else {
            houses_unset_beverage(houses, i, beverage);
        }
    }
}
void houses_unset_beverage(houses_t *houses, uint8_t index, beverage_t beverage) {
    house_unset_beverage(&houses->houses[index], beverage);
    if (house_isset_beverage(&houses->houses[index])) {
        foreach_house {
            if (i != index) {
                house_unset_beverage(&houses->houses[i], houses->houses[index].beverage[0]);
            }
        }
    }
}

void houses_set_color(houses_t *houses, uint8_t index, color_t color) {
    foreach_house {
        if (i == index) {
            house_set_color(&houses->houses[i], color);
        } else {
            houses_unset_color(houses, i, color);
        }
    }
}
void houses_unset_color(houses_t *houses, uint8_t index, color_t color) {
    house_unset_color(&houses->houses[index], color);
    if (house_isset_color(&houses->houses[index])) {
        foreach_house {
            if (i != index) {
                house_unset_color(&houses->houses[i], houses->houses[index].color[0]);
            }
        }
    }
}

void houses_set_pet(houses_t *houses, uint8_t index, pet_t pet) {
    foreach_house {
        if (i == index) {
            house_set_pet(&houses->houses[i], pet);
        } else {
            houses_unset_pet(houses, i, pet);
        }
    }
}
void houses_unset_pet(houses_t *houses, uint8_t index, pet_t pet) {
    house_unset_pet(&houses->houses[index], pet);
    if (house_isset_pet(&houses->houses[index])) {
        foreach_house {
            if (i != index) {
                house_unset_pet(&houses->houses[i], houses->houses[index].pet[0]);
            }
        }
    }
}

void houses_set_hobby(houses_t *houses, uint8_t index, hobby_t hobby) {
    foreach_house {
        if (i == index) {
            house_set_hobby(&houses->houses[i], hobby);
        } else {
            houses_unset_hobby(houses, i, hobby);
        }
    }
}
void houses_unset_hobby(houses_t *houses, uint8_t index, hobby_t hobby) {
    house_unset_hobby(&houses->houses[index], hobby);
    if (house_isset_hobby(&houses->houses[index])) {
        foreach_house {
            if (i != index) {
                house_unset_hobby(&houses->houses[i], houses->houses[index].hobby[0]);
            }
        }
    }
}

void houses_set_nationality(houses_t *houses, uint8_t index, nationality_t nationality) {
    foreach_house {
        if (i == index) {
            house_set_nationality(&houses->houses[i], nationality);
        } else {
            houses_unset_nationality(houses, i, nationality);
        }
    }
}
void houses_unset_nationality(houses_t *houses, uint8_t index, nationality_t nationality) {
    house_unset_nationality(&houses->houses[index], nationality);
    if (house_isset_nationality(&houses->houses[index])) {
        foreach_house {
            if (i != index) {
                house_unset_nationality(&houses->houses[i], houses->houses[index].nationality[0]);
            }
        }
    }
}
