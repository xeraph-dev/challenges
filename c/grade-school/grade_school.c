#include "grade_school.h"

#include <iso646.h>
#include <stdlib.h>
#include <string.h>

static int compare_students(const void *a, const void *b) {
    const student_t *student_a = (const student_t *)a;
    const student_t *student_b = (const student_t *)b;

    if (student_a->grade < student_b->grade)
        return -1;
    if (student_a->grade > student_b->grade)
        return 1;
    return strcmp(student_a->name, student_b->name);
}

void init_roster(roster_t *roster) { roster->count = 0; }

bool add_student(roster_t *roster, char *name, uint8_t grade) {
    student_t *student = {roster->students};
    for (; student < roster->students + roster->count; student++)
        if (strcmp(student->name, name) == 0)
            return false;

    student->grade = grade;
    strcpy(student->name, name);
    roster->count++;

    qsort(roster->students, roster->count, sizeof(student_t), compare_students);
    return true;
}

roster_t get_grade(roster_t *roster, uint8_t grade) {
    roster_t roster_grade = {0};

    const student_t *student = {roster->students};
    const student_t *student_end = roster->students + (roster->count - 1);

    for (; student < roster->students + roster->count; student++)
        if (student->grade == grade)
            break;

    for (; student_end > student; student_end--)
        if (student_end->grade == grade)
            break;

    student_end++;
    roster_grade.count = student_end - student;
    memcpy(roster_grade.students, student,
           sizeof(student_t) * roster_grade.count);

    return roster_grade;
}
