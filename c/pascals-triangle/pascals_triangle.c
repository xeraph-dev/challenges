#include "pascals_triangle.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>

void free_triangle(uint8_t **triangle, size_t rows) {
    for (uint8_t **row = {triangle}; row < triangle + rows; row++)
        free(*row);

    free(triangle);
}

uint8_t **create_triangle(size_t rows) {
    bool is_zero = rows == 0;
    if (is_zero)
        rows++;

    uint8_t **triangle = calloc(rows, sizeof(uint8_t *));
    for (uint8_t **row = {triangle}; row < triangle + rows; row++)
        *row = calloc(rows, sizeof(uint8_t));

    if (is_zero)
        return triangle;

    uint8_t left = {0};
    uint8_t right = {0};
    for (size_t row = {0}; row < rows; row++) {
        for (size_t col = {0}; col < rows; col++) {
            left = col == 0 or row == 0 ? 0 : triangle[row - 1][col - 1];
            right = row == 0 ? (col == 0 ? 1 : 0) : triangle[row - 1][col];
            triangle[row][col] = left + right;
        }
    }

    return triangle;
}
