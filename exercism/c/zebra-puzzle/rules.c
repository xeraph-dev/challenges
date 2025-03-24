#include "rules.h"
#include "house.h"
#include "houses.h"

#include <iso646.h>

void houses_check_rule_2(houses_t *houses) {
    if (houses_is_rule_done(houses, 2)) {
        return;
    }

    foreach_house {
        if (house_has_color(&houses->houses[i], RED)) {
            houses_set_nationality(houses, i, ENGLISHMAN);
            houses_rule_done(houses, 2);
            return;
        } else if (house_has_nationality(&houses->houses[i], ENGLISHMAN)) {
            houses_set_color(houses, i, RED);
            houses_rule_done(houses, 2);
            return;
        }
        if (house_hasnot_color(&houses->houses[i], RED)) {
            houses_unset_nationality(houses, i, ENGLISHMAN);
        } else if (house_hasnot_nationality(&houses->houses[i], ENGLISHMAN)) {
            houses_unset_color(houses, i, RED);
        }
    }
}

void houses_check_rule_3(houses_t *houses) {
    if (houses_is_rule_done(houses, 3)) {
        return;
    }

    foreach_house {
        if (house_has_nationality(&houses->houses[i], SPANIARD)) {
            houses_set_pet(houses, i, DOG);
            houses_rule_done(houses, 3);
            return;
        } else if (house_has_pet(&houses->houses[i], DOG)) {
            houses_set_nationality(houses, i, SPANIARD);
            houses_rule_done(houses, 3);
            return;
        }
        if (house_hasnot_nationality(&houses->houses[i], SPANIARD)) {
            houses_unset_pet(houses, i, DOG);
        } else if (house_hasnot_pet(&houses->houses[i], DOG)) {
            houses_unset_nationality(houses, i, SPANIARD);
        }
    }
}

void houses_check_rule_4(houses_t *houses) {
    if (houses_is_rule_done(houses, 4)) {
        return;
    }

    foreach_house {
        if (house_has_color(&houses->houses[i], GREEN)) {
            houses_set_beverage(houses, i, COFFEE);
            houses_rule_done(houses, 4);
            return;
        } else if (house_has_beverage(&houses->houses[i], COFFEE)) {
            houses_set_color(houses, i, GREEN);
            houses_rule_done(houses, 4);
            return;
        }
        if (house_hasnot_color(&houses->houses[i], GREEN)) {
            houses_unset_beverage(houses, i, COFFEE);
        } else if (house_hasnot_beverage(&houses->houses[i], COFFEE)) {
            houses_unset_color(houses, i, GREEN);
        }
    }
}

void houses_check_rule_5(houses_t *houses) {
    if (houses_is_rule_done(houses, 5)) {
        return;
    }

    foreach_house {
        if (house_has_nationality(&houses->houses[i], UKRAINIAN)) {
            houses_set_beverage(houses, i, TEA);
            houses_rule_done(houses, 5);
            return;
        } else if (house_has_beverage(&houses->houses[i], TEA)) {
            houses_set_nationality(houses, i, UKRAINIAN);
            houses_rule_done(houses, 5);
            return;
        }
        if (house_hasnot_nationality(&houses->houses[i], UKRAINIAN)) {
            houses_unset_beverage(houses, i, TEA);
        } else if (house_hasnot_beverage(&houses->houses[i], TEA)) {
            houses_unset_nationality(houses, i, UKRAINIAN);
        }
    }
}

void houses_check_rule_6(houses_t *houses) {
    if (houses_is_rule_done(houses, 6)) {
        return;
    }

    houses_unset_color(houses, 0, GREEN);
    houses_unset_color(houses, HOUSES - 1, IVORY);

    foreach_house {
        if (house_has_color(&houses->houses[i], GREEN)) {
            houses_set_color(houses, i - 1, IVORY);
            houses_rule_done(houses, 6);
            return;
        } else if (house_has_color(&houses->houses[i], IVORY)) {
            houses_set_color(houses, i + 1, GREEN);
            houses_rule_done(houses, 6);
            return;
        }
        if (house_hasnot_color(&houses->houses[i], GREEN) and house_hasnot_color(&houses->houses[i], IVORY)) {
            if (i > 0) {
                houses_unset_color(houses, i - 1, IVORY);
            }
            if (i < (HOUSES - 1)) {
                houses_unset_color(houses, i + 1, GREEN);
            }
        }
    }
}

void houses_check_rule_7(houses_t *houses) {
    if (houses_is_rule_done(houses, 7)) {
        return;
    }

    foreach_house {
        if (house_has_pet(&houses->houses[i], SNAIL)) {
            houses_set_hobby(houses, i, DANCE);
            houses_rule_done(houses, 7);
            return;
        } else if (house_has_hobby(&houses->houses[i], DANCE)) {
            houses_set_pet(houses, i, SNAIL);
            houses_rule_done(houses, 7);
            return;
        }
        if (house_hasnot_pet(&houses->houses[i], SNAIL)) {
            houses_unset_hobby(houses, i, DANCE);
        } else if (house_hasnot_hobby(&houses->houses[i], DANCE)) {
            houses_unset_pet(houses, i, SNAIL);
        }
    }
}

void houses_check_rule_8(houses_t *houses) {
    if (houses_is_rule_done(houses, 8)) {
        return;
    }

    foreach_house {
        if (house_has_color(&houses->houses[i], YELLOW)) {
            houses_set_hobby(houses, i, PAINT);
            houses_rule_done(houses, 8);
            return;
        } else if (house_has_hobby(&houses->houses[i], PAINT)) {
            houses_set_color(houses, i, YELLOW);
            houses_rule_done(houses, 8);
            return;
        }
        if (house_hasnot_color(&houses->houses[i], YELLOW)) {
            houses_unset_hobby(houses, i, PAINT);
        } else if (house_hasnot_hobby(&houses->houses[i], PAINT)) {
            houses_unset_color(houses, i, YELLOW);
        }
    }
}

void houses_check_rule_9(houses_t *houses) {
    if (houses_is_rule_done(houses, 9)) {
        return;
    }

    houses_set_beverage(houses, 2, MILK);
    houses_rule_done(houses, 9);
}

void houses_check_rule_10(houses_t *houses) {
    if (houses_is_rule_done(houses, 10)) {
        return;
    }

    houses_set_nationality(houses, 0, NORWEGIAN);
    houses_rule_done(houses, 10);
}

void houses_check_rule_11(houses_t *houses) {
    if (houses_is_rule_done(houses, 11)) {
        return;
    }

    foreach_house {
        if (house_has_hobby(&houses->houses[i], READ)) {
            if (house_is_last(i) or house_hasnot_pet(&houses->houses[i + 1], FOX)) {
                houses_set_pet(houses, i - 1, FOX);
                houses_rule_done(houses, 11);
                return;
            } else if (house_is_first(i) or house_hasnot_pet(&houses->houses[i - 1], FOX)) {
                houses_set_pet(houses, i + 1, FOX);
                houses_rule_done(houses, 11);
                return;
            }
        } else if (house_has_pet(&houses->houses[i], FOX)) {
            if (house_is_last(i) or house_hasnot_hobby(&houses->houses[i + 1], READ)) {
                houses_set_hobby(houses, i - 1, READ);
                houses_rule_done(houses, 11);
                return;
            } else if (house_is_first(i) or house_hasnot_hobby(&houses->houses[i - 1], READ)) {
                houses_set_hobby(houses, i + 1, READ);
                houses_rule_done(houses, 11);
                return;
            }
        }
        if ((house_is_first(i) or house_hasnot_hobby(&houses->houses[i - 1], READ)) and
            (house_is_last(i) or house_hasnot_hobby(&houses->houses[i + 1], READ))) {
            houses_unset_pet(houses, i, FOX);
        } else if ((house_is_first(i) or house_hasnot_pet(&houses->houses[i - 1], FOX)) and
                   (house_is_last(i) or house_hasnot_pet(&houses->houses[i + 1], FOX))) {
            houses_unset_hobby(houses, i, READ);
        }
    }
}

void houses_check_rule_12(houses_t *houses) {
    if (houses_is_rule_done(houses, 12)) {
        return;
    }

    foreach_house {
        if (house_has_hobby(&houses->houses[i], PAINT)) {
            if (house_is_last(i) or house_hasnot_pet(&houses->houses[i + 1], HORSE)) {
                houses_set_pet(houses, i - 1, HORSE);
                houses_rule_done(houses, 12);
                return;
            } else if (house_is_first(i) or house_hasnot_pet(&houses->houses[i - 1], HORSE)) {
                houses_set_pet(houses, i + 1, HORSE);
                houses_rule_done(houses, 12);
                return;
            }
        } else if (house_has_pet(&houses->houses[i], HORSE)) {
            if (house_is_last(i) or house_hasnot_hobby(&houses->houses[i + 1], PAINT)) {
                houses_set_hobby(houses, i - 1, PAINT);
                houses_rule_done(houses, 12);
                return;
            } else if (house_is_first(i) or house_hasnot_hobby(&houses->houses[i + 1], PAINT)) {
                houses_set_hobby(houses, i + 1, PAINT);
                houses_rule_done(houses, 12);
                return;
            }
        }
        if ((house_is_first(i) or house_hasnot_hobby(&houses->houses[i - 1], PAINT)) and
            (house_is_last(i) or house_hasnot_hobby(&houses->houses[i + 1], PAINT))) {
            houses_unset_pet(houses, i, HORSE);
        } else if ((house_is_first(i) or house_hasnot_pet(&houses->houses[i - 1], HORSE)) and
                   (house_is_last(i) or house_hasnot_pet(&houses->houses[i + 1], HORSE))) {
            houses_unset_hobby(houses, i, PAINT);
        }
    }
}

void houses_check_rule_13(houses_t *houses) {
    if (houses_is_rule_done(houses, 13)) {
        return;
    }

    foreach_house {
        if (house_has_hobby(&houses->houses[i], FOOTBALL)) {
            houses_set_beverage(houses, i, JUICE);
            houses_rule_done(houses, 13);
            return;
        } else if (house_has_beverage(&houses->houses[i], JUICE)) {
            houses_set_hobby(houses, i, FOOTBALL);
            houses_rule_done(houses, 13);
            return;
        }
        if (house_hasnot_hobby(&houses->houses[i], FOOTBALL)) {
            houses_unset_beverage(houses, i, JUICE);
        } else if (house_hasnot_beverage(&houses->houses[i], JUICE)) {
            houses_unset_hobby(houses, i, FOOTBALL);
        }
    }
    houses_rule_done(houses, 13);
}

void houses_check_rule_14(houses_t *houses) {
    if (houses_is_rule_done(houses, 14)) {
        return;
    }

    foreach_house {
        if (house_has_nationality(&houses->houses[i], JAPANESE)) {
            houses_set_hobby(houses, i, CHESS);
            houses_rule_done(houses, 14);
            return;
        } else if (house_has_hobby(&houses->houses[i], CHESS)) {
            houses_set_nationality(houses, i, JAPANESE);
            houses_rule_done(houses, 14);
            return;
        }
        if (house_hasnot_nationality(&houses->houses[i], JAPANESE)) {
            houses_unset_hobby(houses, i, CHESS);
        } else if (house_hasnot_hobby(&houses->houses[i], CHESS)) {
            houses_unset_nationality(houses, i, JAPANESE);
        }
    }
}

void houses_check_rule_15(houses_t *houses) {
    if (houses_is_rule_done(houses, 15)) {
        return;
    }

    foreach_house {
        if (house_has_color(&houses->houses[i], BLUE)) {
            if (house_is_last(i) or house_hasnot_nationality(&houses->houses[i + 1], NORWEGIAN)) {
                houses_set_nationality(houses, i - 1, NORWEGIAN);
                houses_rule_done(houses, 15);
                return;
            } else if (house_is_first(i) or house_hasnot_nationality(&houses->houses[i - 1], NORWEGIAN)) {
                houses_set_nationality(houses, i + 1, NORWEGIAN);
                houses_rule_done(houses, 15);
                return;
            }
        } else if (house_has_nationality(&houses->houses[i], NORWEGIAN)) {
            if (house_is_last(i) or house_hasnot_color(&houses->houses[i + 1], BLUE)) {
                houses_set_color(houses, i - 1, BLUE);
                houses_rule_done(houses, 15);
                return;
            } else if (house_is_first(i) or house_hasnot_color(&houses->houses[i + 1], BLUE)) {
                houses_set_color(houses, i + 1, BLUE);
                houses_rule_done(houses, 15);
                return;
            }
        }
        if ((house_is_first(i) or house_hasnot_color(&houses->houses[i - 1], BLUE)) and
            (house_is_last(i) or house_hasnot_color(&houses->houses[i + 1], BLUE))) {
            houses_unset_nationality(houses, i, NORWEGIAN);
        } else if ((house_is_first(i) or house_hasnot_nationality(&houses->houses[i - 1], NORWEGIAN)) and
                   (house_is_last(i) or house_hasnot_nationality(&houses->houses[i + 1], NORWEGIAN))) {
            houses_unset_color(houses, i, BLUE);
        }
    }
}
