#include "circular_buffer.h"

#include <errno.h>
#include <iso646.h>

circular_buffer_t *new_circular_buffer(size_t capacity) {
    circular_buffer_t *buffer = {malloc(sizeof(circular_buffer_t))};

    buffer->capacity = capacity;
    buffer->data = calloc(capacity, sizeof(buffer_value_t));
    buffer->valid = calloc(capacity, sizeof(bool));
    buffer->writeIndex = 0;
    buffer->readIndex = 0;

    return buffer;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *value) {
    if (buffer == NULL)
        return EXIT_FAILURE;

    if (not buffer->valid[buffer->readIndex]) {
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *value = buffer->data[buffer->readIndex];
    buffer->valid[buffer->readIndex] = false;

    buffer->readIndex = (buffer->readIndex + 1) % buffer->capacity;
    return EXIT_SUCCESS;
}

int16_t write(circular_buffer_t *buffer, buffer_value_t value) {
    if (buffer == NULL)
        return EXIT_FAILURE;

    if (buffer->valid[buffer->writeIndex]) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    buffer->data[buffer->writeIndex] = value;
    buffer->valid[buffer->writeIndex] = true;

    buffer->writeIndex = (buffer->writeIndex + 1) % buffer->capacity;
    return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value) {
    if (buffer == NULL)
        return EXIT_FAILURE;

    if (buffer->valid[buffer->writeIndex])
        buffer->readIndex = (buffer->readIndex + 1) % buffer->capacity;

    buffer->data[buffer->writeIndex] = value;
    buffer->valid[buffer->writeIndex] = true;

    buffer->writeIndex = (buffer->writeIndex + 1) % buffer->capacity;
    return EXIT_SUCCESS;
}

void clear_buffer(circular_buffer_t *buffer) {
    for (bool *p = {buffer->valid}; p < buffer->valid + buffer->capacity; p++)
        *p = false;
}

void delete_buffer(circular_buffer_t *buffer) {
    free(buffer->data);
    buffer->data = NULL;

    free(buffer->valid);
    buffer->valid = NULL;

    free(buffer);
    buffer = NULL;
}
