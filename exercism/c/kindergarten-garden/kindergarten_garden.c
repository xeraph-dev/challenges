#include "kindergarten_garden.h"

#include <stdio.h>
#include <string.h>

static plant_t plant(const char *p) {
    switch (*p) {
    case 'C':
        return CLOVER;
    case 'G':
        return GRASS;
    case 'R':
        return RADISHES;
    case 'V':
        return VIOLETS;
    }
    return -1;
}

plants_t plants(const char *diagram, const char *student) {
    plants_t p = {0};

    int offset = 2 * (strcmp(student, "Alice") == 0     ? 0
                      : strcmp(student, "Bob") == 0     ? 1
                      : strcmp(student, "Charlie") == 0 ? 2
                      : strcmp(student, "David") == 0   ? 3
                      : strcmp(student, "Eve") == 0     ? 4
                      : strcmp(student, "Fred") == 0    ? 5
                      : strcmp(student, "Ginny") == 0   ? 6
                      : strcmp(student, "Harriet") == 0 ? 7
                      : strcmp(student, "Ileana") == 0  ? 8
                      : strcmp(student, "Joseph") == 0  ? 9
                      : strcmp(student, "Kincaid") == 0 ? 10
                      : strcmp(student, "Larry") == 0   ? 11
                                                        : -1);

    p.plants[0] = plant(diagram + offset);
    p.plants[1] = plant(diagram + offset + 1);
    diagram = strchr(diagram, '\n') + 1;
    p.plants[2] = plant(diagram + offset);
    p.plants[3] = plant(diagram + offset + 1);

    return p;
}
