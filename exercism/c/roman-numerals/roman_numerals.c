#include "roman_numerals.h"

#include <iso646.h>
#include <stdlib.h>
#include <string.h>

char *to_roman_numeral(unsigned int number) {
    size_t roman_len = {0};
    char *roman = calloc(roman_len, sizeof(char));
    while (number > 0) {
        if (number >= 1000) {
            number -= 1000;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "M");
        } else if (number >= 900) {
            number -= 900;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "CM");
        } else if (number >= 500 and number < 900) {
            number -= 500;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "D");
        } else if (number >= 400) {
            number -= 400;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "CD");
        } else if (number >= 100 and number < 400) {
            number -= 100;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "C");
        } else if (number >= 90) {
            number -= 90;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "XC");
        } else if (number >= 50 and number < 90) {
            number -= 50;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "L");
        } else if (number >= 40) {
            number -= 40;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "XL");
        } else if (number >= 10 and number < 40) {
            number -= 10;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "X");
        } else if (number >= 9) {
            number -= 9;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "IX");
        } else if (number >= 5 and number < 9) {
            number -= 5;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "V");
        } else if (number >= 4) {
            number -= 4;
            roman = realloc(roman, roman_len += 2);
            strcat(roman, "IV");
        } else if (number >= 1 and number < 4) {
            number -= 1;
            roman = realloc(roman, roman_len += 1);
            strcat(roman, "I");
        }
    }
    return roman;
}
