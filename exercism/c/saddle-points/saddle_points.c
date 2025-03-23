#include "saddle_points.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

saddle_points_t *saddle_points(uint8_t row_size, uint8_t column_size,
                               uint8_t matrix[row_size][column_size]) {
    saddle_points_t *points =
        malloc(sizeof(saddle_points_t) +
               column_size * row_size * sizeof(saddle_point_t));

    points->count = 0;

    for (size_t row = {0}; row < row_size; row++) {
        uint8_t largest = {0};
        for (size_t column = {0}; column < column_size; column++) {
            if (matrix[row][column] > largest) {
                largest = matrix[row][column];
            }
        }

        for (size_t column = {0}; column < column_size; column++) {
            if (matrix[row][column] == largest) {
                bool is_lowest_row = {true};
                for (size_t row = {0}; row < row_size; row++) {
                    if (largest > matrix[row][column]) {
                        is_lowest_row = false;
                    }
                }

                if (is_lowest_row) {
                    points->points[points->count++] =
                        (saddle_point_t){row + 1, column + 1};
                }
            }
        }
    }

    return points;
}

void free_saddle_points(saddle_points_t *points) { free(points); }
