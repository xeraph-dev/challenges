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

    triangle[0][0] = 1;
    for (size_t row = {1}; row < rows; row++) {
        triangle[row][0] = 1;
        for (size_t col = {1}; col < rows; col++) {
            uint8_t left = triangle[row - 1][col - 1];
            uint8_t right = triangle[row - 1][col];
            triangle[row][col] = left + right;
        }
    }

    return triangle;
}
