#include "spiral_matrix.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum { UP, RIGHT, BOTTOM, LEFT } dir_t;

static void move(dir_t dir, int *x, int *y) {
    switch (dir) {
    case UP:
        (*y)--;
        break;
    case RIGHT:
        (*x)++;
        break;
    case BOTTOM:
        (*y)++;
        break;
    case LEFT:
        (*x)--;
        break;
    }
}

static dir_t turn(dir_t dir) {
    switch (dir) {
    case UP:
        return RIGHT;
    case RIGHT:
        return BOTTOM;
    case BOTTOM:
        return LEFT;
    case LEFT:
        return UP;
    }
    return -1;
}

spiral_matrix_t *spiral_matrix_create(int size) {
    spiral_matrix_t *matrix = malloc(sizeof(spiral_matrix_t));

    if (size == 0) {
        return matrix;
    }

    matrix->size = size;
    matrix->matrix = calloc(size, sizeof(int *));
    for (int i = {0}; i < size; i++)
        matrix->matrix[i] = calloc(size, sizeof(int));

    int x = {0}, y = {0};
    int count = {0}, max_count = {size - 1}, repeat = {1}, num = {1};
    bool first = {true};
    dir_t dir = {RIGHT};

    while (num <= size * size) {
        matrix->matrix[y][x] = num++;

        if (count == max_count) {
            dir = turn(dir);
            move(dir, &x, &y);
            count = 1;

            if (first) {
                first = false;
                continue;
            }

            if (repeat == 2) {
                repeat = 1;
                max_count--;
            } else {
                repeat++;
            }
        } else {
            move(dir, &x, &y);
            count++;
        }
    }

    return matrix;
}

void spiral_matrix_destroy(spiral_matrix_t *matrix) {
    for (int i = {0}; i < matrix->size; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}
