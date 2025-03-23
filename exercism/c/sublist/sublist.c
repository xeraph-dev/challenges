#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>

#include "sublist.h"

static bool contains(int *list_a, int *list_b, size_t list_a_size,
                     size_t list_b_size) {
    for (size_t i = 0; i <= list_a_size - list_b_size; i++) {
        size_t j = 0;
        while (j < list_b_size && list_a[i + j] == list_b[j])
            j++;
        if (j == list_b_size)
            return true;
    }
    return false;
}

comparison_result_t check_lists(int *list_a, int *list_b, size_t list_a_size,
                                size_t list_b_size) {
    if (list_a_size == list_b_size and
        contains(list_a, list_b, list_a_size, list_b_size))
        return EQUAL;
    if (list_a_size > list_b_size and
        contains(list_a, list_b, list_a_size, list_b_size))
        return SUPERLIST;
    if (list_a_size < list_b_size and
        contains(list_b, list_a, list_b_size, list_a_size))
        return SUBLIST;
    return UNEQUAL;
}
