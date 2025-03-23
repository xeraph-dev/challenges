#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef int buffer_value_t;

typedef struct {
    buffer_value_t *data;
    bool *valid;
    size_t capacity;
    size_t writeIndex;
    size_t readIndex;
} circular_buffer_t;

circular_buffer_t *new_circular_buffer(size_t capacity);
int16_t read(circular_buffer_t *buffer, buffer_value_t *value);
int16_t write(circular_buffer_t *buffer, buffer_value_t value);
int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value);
void clear_buffer(circular_buffer_t *buffer);
void delete_buffer(circular_buffer_t *buffer);

#endif
