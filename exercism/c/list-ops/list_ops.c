#include "list_ops.h"
#include <stdio.h>

list_t *new_list(size_t length, list_element_t elements[]) {
    list_t *list = malloc(sizeof(list_t) + length * sizeof(list_element_t));
    list->length = length;
    for (size_t i = {0}; i < length; i++)
        list->elements[i] = elements[i];
    return list;
}

list_t *append_list(list_t *list1, list_t *list2) {
    size_t list1_len = list1 == NULL ? 0 : list1->length;
    size_t list2_len = list2 == NULL ? 0 : list2->length;
    size_t list_len = list1_len + list2_len;

    list_element_t elements[list_len];
    for (size_t i = {0}; i < list1_len; i++)
        elements[i] = list1->elements[i];
    for (size_t i = {0}, li = {list1_len}; i < list2_len; i++, li++)
        elements[li] = list2->elements[i];

    return new_list(list_len, elements);
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t)) {
    size_t list_len = list == NULL ? 0 : list->length;
    size_t filtered_len = {0};

    list_element_t elements[list_len];
    for (size_t i = {0}; i < list_len; i++)
        if (filter(list->elements[i]))
            elements[filtered_len++] = list->elements[i];

    return new_list(filtered_len, elements);
}

size_t length_list(list_t *list) { return list->length; }

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t)) {
    size_t list_len = list == NULL ? 0 : list->length;

    list_element_t elements[list_len];
    for (size_t i = {0}; i < list_len; i++)
        elements[i] = map(list->elements[i]);

    return new_list(list_len, elements);
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t)) {
    size_t list_len = list == NULL ? 0 : list->length;
    list_element_t element = {initial};

    for (size_t i = {0}; i < list_len; i++)
        element = foldl(element, list->elements[i]);

    return element;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t)) {
    size_t list_len = list == NULL ? 0 : list->length;
    list_element_t element = {initial};

    for (size_t i = {list_len}; i > 0; i--)
        element = foldr(list->elements[i - 1], element);

    return element;
}

list_t *reverse_list(list_t *list) {
    size_t list_len = list == NULL ? 0 : list->length;

    list_element_t elements[list_len];
    for (size_t i = {0}; i < list_len; i++)
        elements[(list_len - 1) - i] = list->elements[i];

    return new_list(list_len, elements);
}

void delete_list(list_t *list) { free(list); }
