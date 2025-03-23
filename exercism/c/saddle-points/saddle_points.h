#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t row;
    uint8_t column;
} saddle_point_t;

typedef struct {
    size_t count;
    saddle_point_t points[];
} saddle_points_t;

saddle_points_t *saddle_points(uint8_t column_size, uint8_t row_size,
                               uint8_t matrix[column_size][row_size]);

void free_saddle_points(saddle_points_t *points);

#endif
