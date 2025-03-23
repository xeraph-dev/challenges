#include "phone_number.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void drop_separators(const char **input) {
    while (**input == ' ' or **input == '.' or **input == '-') {
        (*input)++;
    }
}

static char *parse_country_code(const char **input) {
    char *country = {calloc(2, sizeof(char))};
    strcpy(country, "0");

    if (**input == '\0') {
        free(country);
        return NULL;
    }

    if (**input == '+') {
        (*input)++;
    }

    if (**input == '1') {
        *country = '1';
        (*input)++;
    }

    return country;
}

static char *parse_area_code(const char **input) {
    char *area = {calloc(4, sizeof(char))};
    strcpy(area, "000");
    bool first = {true};

    if (**input == '(') {
        (*input)++;
    }

    for (char *p = {area}; *p != '\0'; p++) {
        if (**input == '\0') {
            free(area);
            return NULL;
        }

        char lower = first ? '2' : '0';
        if (**input >= lower and **input <= '9') {
            *p = **input;
            (*input)++;
        } else {
            free(area);
            return NULL;
        }
        if (first) {
            first = false;
        }
    }

    if (**input == ')') {
        (*input)++;
    }

    return area;
}

static char *parse_exchange_code(const char **input) {
    char *exchange = {calloc(4, sizeof(char))};
    strcpy(exchange, "000");
    bool first = {true};

    for (char *p = {exchange}; *p != '\0'; p++) {
        if (**input == '\0') {
            free(exchange);
            return NULL;
        }

        char lower = first ? '2' : '0';
        if (**input >= lower and **input <= '9') {
            *p = **input;
            (*input)++;
        } else {
            free(exchange);
            return NULL;
        }
        if (first) {
            first = false;
        }
    }

    return exchange;
}

static char *parse_subscriber_number(const char **input) {
    char *subscriber = {calloc(5, sizeof(char))};
    strcpy(subscriber, "0000");

    for (char *p = {subscriber}; *p != '\0'; p++) {
        if (**input == '\0') {
            free(subscriber);
            return NULL;
        }

        if (**input >= '0' and **input <= '9') {
            *p = **input;
            (*input)++;
        } else {
            free(subscriber);
            return NULL;
        }
    }

    return subscriber;
}

char *phone_number_clean(const char *input) {
    char *number = {calloc(12, sizeof(char))};
    strcpy(number, "0000000000");

    char *country = NULL, *area = NULL, *exchange = NULL, *subscriber = NULL;

    drop_separators(&input);
    if ((country = parse_country_code(&input)) == NULL) {
        goto end;
    }
    drop_separators(&input);
    if ((area = parse_area_code(&input)) == NULL) {
        goto end;
    }
    drop_separators(&input);
    if ((exchange = parse_exchange_code(&input)) == NULL) {
        goto end;
    }
    drop_separators(&input);
    if ((subscriber = parse_subscriber_number(&input)) == NULL) {
        goto end;
    }
    drop_separators(&input);
    if (*input != '\0') {
        goto end;
    }

    strncpy(number, area, 3);
    strncpy(number + 3, exchange, 3);
    strncpy(number + 3 + 3, subscriber, 4);

end:
    if (country != NULL) {
        free(country);
    }
    if (area != NULL) {
        free(area);
    }
    if (exchange != NULL) {
        free(exchange);
    }
    if (subscriber != NULL) {
        free(subscriber);
    }

    return number;
}
