#include "house.h"

#include <iso646.h>
#include <stddef.h>

char *beverage_string(beverage_t beverage) {
    switch (beverage) {
    case BEVERAGE_UNSET:
        return "";
    case COFFEE:
        return "Coffee";
    case MILK:
        return "Milk";
    case TEA:
        return "Tea";
    case JUICE:
        return "Juice";
    case WATER:
        return "Water";
    }
    return NULL;
}

char *color_string(color_t color) {
    switch (color) {
    case COLOR_UNSET:
        return "";
    case RED:
        return "Red";
    case BLUE:
        return "Blue";
    case YELLOW:
        return "Yellow";
    case GREEN:
        return "Green";
    case IVORY:
        return "Ivory";
    }
    return NULL;
}

char *pet_string(pet_t pet) {
    switch (pet) {
    case PET_UNSET:
        return "";
    case SNAIL:
        return "Snail";
    case FOX:
        return "Fox";
    case HORSE:
        return "Horse";
    case DOG:
        return "Dog";
    case ZEBRA:
        return "Zebra";
    }
    return NULL;
}

char *hobby_string(hobby_t hobby) {
    switch (hobby) {
    case HOBBY_UNSET:
        return "";
    case PAINT:
        return "Paint";
    case DANCE:
        return "Dance";
    case READ:
        return "Read";
    case FOOTBALL:
        return "Football";
    case CHESS:
        return "Chess";
    }
    return NULL;
}

char *nationality_string(nationality_t country) {
    switch (country) {
    case NATIONALITY_UNSET:
        return "";
    case SPANIARD:
        return "Spaniard";
    case ENGLISHMAN:
        return "Englishman";
    case UKRAINIAN:
        return "Ukrainian";
    case JAPANESE:
        return "Japanese";
    case NORWEGIAN:
        return "Norwegian";
    }
    return NULL;
}

house_t house_create(void) {
    return (house_t){
        .beverage = {COFFEE, MILK, TEA, JUICE, WATER},
        .color = {RED, BLUE, YELLOW, GREEN, IVORY},
        .pet = {SNAIL, FOX, HORSE, DOG, ZEBRA},
        .hobby = {PAINT, DANCE, READ, FOOTBALL, CHESS},
        .nationality = {SPANIARD, ENGLISHMAN, UKRAINIAN, JAPANESE, NORWEGIAN},

        .beverage_len = HOUSES,
        .color_len = HOUSES,
        .pet_len = HOUSES,
        .hobby_len = HOUSES,
        .nationality_len = HOUSES,
    };
}

bool house_is_first(uint8_t index) { return index == 0; }
bool house_is_last(uint8_t index) { return index == (HOUSES - 1); }

bool house_hasnot_beverage(const house_t *house, beverage_t beverage) {
    return house_isset_beverage(house) and house->beverage[0] != beverage;
}
bool house_has_beverage(const house_t *house, beverage_t beverage) {
    return house_isset_beverage(house) and house->beverage[0] == beverage;
}
bool house_isset_beverage(const house_t *house) { return house->beverage_len == 1; }
void house_set_beverage(house_t *house, beverage_t beverage) {
    foreach_house { house->beverage[i] = i == 0 ? beverage : BEVERAGE_UNSET; }
    house->beverage_len = 1;
}
void house_unset_beverage(house_t *house, beverage_t beverage) {
    foreach_house {
        if (house->beverage[i] == beverage) {
            house->beverage[i] = BEVERAGE_UNSET;
            house->beverage_len--;
            break;
        }
    }
    if (house_isset_beverage(house)) {
        foreach_house {
            if (i > 0 and house->beverage[i] != BEVERAGE_UNSET) {
                house->beverage[0] = house->beverage[i];
                house->beverage[i] = BEVERAGE_UNSET;
                break;
            }
        }
    }
}

bool house_hasnot_color(const house_t *house, color_t color) {
    return house_isset_color(house) and house->color[0] != color;
}
bool house_has_color(const house_t *house, color_t color) {
    return house_isset_color(house) and house->color[0] == color;
}
bool house_isset_color(const house_t *house) { return house->color_len == 1; }
void house_set_color(house_t *house, color_t color) {
    foreach_house { house->color[i] = i == 0 ? color : COLOR_UNSET; }
    house->color_len = 1;
}
void house_unset_color(house_t *house, color_t color) {
    foreach_house {
        if (house->color[i] == color) {
            house->color[i] = COLOR_UNSET;
            house->color_len--;
            break;
        }
    }
    if (house_isset_color(house)) {
        foreach_house {
            if (i > 0 and house->color[i] != COLOR_UNSET) {
                house->color[0] = house->color[i];
                house->color[i] = COLOR_UNSET;
                break;
            }
        }
    }
}

bool house_hasnot_pet(const house_t *house, pet_t pet) { return house_isset_pet(house) and house->pet[0] != pet; }
bool house_has_pet(const house_t *house, pet_t pet) { return house_isset_pet(house) and house->pet[0] == pet; }
bool house_isset_pet(const house_t *house) { return house->pet_len == 1; }
void house_set_pet(house_t *house, pet_t pet) {
    foreach_house { house->pet[i] = i == 0 ? pet : PET_UNSET; }
    house->pet_len = 1;
}
void house_unset_pet(house_t *house, pet_t pet) {
    foreach_house {
        if (house->pet[i] == pet) {
            house->pet[i] = PET_UNSET;
            house->pet_len--;
            break;
        }
    }
    if (house_isset_pet(house)) {
        foreach_house {
            if (i > 0 and house->pet[i] != PET_UNSET) {
                house->pet[0] = house->pet[i];
                house->pet[i] = PET_UNSET;
                break;
            }
        }
    }
}

bool house_hasnot_hobby(const house_t *house, hobby_t hobby) {
    return house_isset_hobby(house) and house->hobby[0] != hobby;
}
bool house_has_hobby(const house_t *house, hobby_t hobby) {
    return house_isset_hobby(house) and house->hobby[0] == hobby;
}
bool house_isset_hobby(const house_t *house) { return house->hobby_len == 1; }
void house_set_hobby(house_t *house, hobby_t hobby) {
    foreach_house { house->hobby[i] = i == 0 ? hobby : HOBBY_UNSET; }
    house->hobby_len = 1;
}
void house_unset_hobby(house_t *house, hobby_t hobby) {
    foreach_house {
        if (house->hobby[i] == hobby) {
            house->hobby[i] = HOBBY_UNSET;
            house->hobby_len--;
            break;
        }
    }
    if (house_isset_hobby(house)) {
        foreach_house {
            if (i > 0 and house->hobby[i] != HOBBY_UNSET) {
                house->hobby[0] = house->hobby[i];
                house->hobby[i] = HOBBY_UNSET;
                break;
            }
        }
    }
}

bool house_hasnot_nationality(const house_t *house, nationality_t nationality) {
    return house_isset_nationality(house) and house->nationality[0] != nationality;
}
bool house_has_nationality(const house_t *house, nationality_t nationality) {
    return house_isset_nationality(house) and house->nationality[0] == nationality;
}
bool house_isset_nationality(const house_t *house) { return house->nationality_len == 1; }
void house_set_nationality(house_t *house, nationality_t country) {
    foreach_house { house->nationality[i] = i == 0 ? country : NATIONALITY_UNSET; }
    house->nationality_len = 1;
}
void house_unset_nationality(house_t *house, nationality_t country) {
    foreach_house {
        if (house->nationality[i] == country) {
            house->nationality[i] = NATIONALITY_UNSET;
            house->nationality_len--;
            break;
        }
    }
    if (house_isset_nationality(house)) {
        foreach_house {
            if (i > 0 and house->nationality[i] != NATIONALITY_UNSET) {
                house->nationality[0] = house->nationality[i];
                house->nationality[i] = NATIONALITY_UNSET;
                break;
            }
        }
    }
}
