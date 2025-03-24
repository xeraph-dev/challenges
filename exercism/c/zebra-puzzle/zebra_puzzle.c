#include "zebra_puzzle.h"

#include "house.h"
#include "rules.h"

#include <iso646.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// ✅ 1. There are five houses.
// 2. The Englishman lives in the red house.
// 3. The Spaniard owns the dog.
// 4. The person in the green house drinks coffee.
// 5. The Ukrainian drinks tea.
// 6. The green house is immediately to the right of the ivory house.
// 7. The snail owner likes to go dancing.
// ✅ 8. The person in the yellow house is a painter.
// ✅ 9. The person in the middle house drinks milk.
// ✅ 10. The Norwegian lives in the first house.
// 11. The person who enjoys reading lives in the house next to the person with
//     the fox.
// ✅ 12. The painter's house is next to the house with the horse.
// 13. The person who plays football drinks orange juice.
// 14. The Japanese person plays chess.
// ✅ 15. The Norwegian lives next to the blue house.

static void houses_print(houses_t *houses) {
    static char *data[6][6] = {
        {"House", "1", "2", "3", "4", "5"}, {"Beverage"}, {"Color"}, {"Pet"}, {"Hobby"}, {"Nationality"},
    };
    foreach_house {
        if (house_isset_beverage(&houses->houses[i])) {
            data[1][i + 1] = beverage_string(houses->houses[i].beverage[0]);
        } else {
            data[1][i + 1] = "";
        }
        if (house_isset_color(&houses->houses[i])) {
            data[2][i + 1] = color_string(houses->houses[i].color[0]);
        } else {
            data[2][i + 1] = "";
        }
        if (house_isset_pet(&houses->houses[i])) {
            data[3][i + 1] = pet_string(houses->houses[i].pet[0]);
        } else {
            data[3][i + 1] = "";
        }
        if (house_isset_hobby(&houses->houses[i])) {
            data[4][i + 1] = hobby_string(houses->houses[i].hobby[0]);
        } else {
            data[4][i + 1] = "";
        }
        if (house_isset_nationality(&houses->houses[i])) {
            data[5][i + 1] = nationality_string(houses->houses[i].nationality[0]);
        } else {
            data[5][i + 1] = "";
        }
    }

    for (int y = {0}; y < 6; y++) {
        for (int x = {0}; x < 6; x++) {
            printf("%12s", data[y][x]);
            if (x < 5) {
                printf(" | ");
            }
        }

        printf("\n");
    }
    printf("\n");
}

solution_t solve_puzzle(void) {
    houses_t houses = houses_create();

    while (not houses_is_completed(&houses)) {
        houses_check_rule_2(&houses);
        houses_check_rule_3(&houses);
        houses_check_rule_4(&houses);
        houses_check_rule_5(&houses);
        houses_check_rule_6(&houses);
        houses_check_rule_7(&houses);
        houses_check_rule_8(&houses);
        houses_check_rule_9(&houses);
        houses_check_rule_10(&houses);
        houses_check_rule_11(&houses);
        houses_check_rule_12(&houses);
        houses_check_rule_13(&houses);
        houses_check_rule_14(&houses);
        houses_check_rule_15(&houses);
        houses_print(&houses);
    }

    return houses_solution(&houses);
}
