#include <iso646.h>

#include "yacht.h"

int score(dice_t dice, category_t category) {
    int faces[6] = {0};

    for (int *face = {dice.faces}; face < dice.faces + 5; face++)
        faces[(*face) - 1]++;

    switch (category) {
    case ONES:
    case TWOS:
    case THREES:
    case FOURS:
    case FIVES:
    case SIXES: {
        return faces[category] * (category + 1);
    }
    case FULL_HOUSE: {
        int two = {0};
        int three = {0};
        int i = {1};
        for (int *face = {faces}; face < faces + 6; face++, i++)
            if (*face == 2)
                two = i;
            else if (*face == 3)
                three = i;
        if (three == 0 or two == 0)
            return 0;
        return three * 3 + two * 2;
    }
    case FOUR_OF_A_KIND: {
        int i = {1};
        for (int *face = {faces}; face < faces + 6; face++, i++)
            if (*face >= 4)
                return i * 4;
        return 0;
    }
    case LITTLE_STRAIGHT: {
        int valid = {0};
        for (int *face = {faces}; face < faces + 5; face++)
            if (*face == 1)
                valid++;
        if (valid == 5)
            return 30;
        return 0;
    }
    case BIG_STRAIGHT: {
        int valid = {0};
        for (int *face = {faces + 1}; face < faces + 6; face++)
            if (*face == 1)
                valid++;
        if (valid == 5)
            return 30;
        return 0;
    }
    case CHOICE: {
        int sum = {0};
        int i = {1};
        for (int *face = {faces}; face < faces + 6; face++, i++)
            sum += i * *face;
        return sum;
    }
    case YACHT: {
        for (int *face = {faces}; face < faces + 6; face++)
            if (*face == 5)
                return 50;
        return 0;
    }
    }
    return 0;
}
