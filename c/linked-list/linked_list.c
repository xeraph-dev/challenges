#include "linked_list.h"

#include <iso646.h>
#include <stdlib.h>

struct list_node {
    struct list_node *prev, *next;
    ll_data_t data;
};

struct list {
    size_t size;
    struct list_node *first, *last;
};

static struct list_node *list_node_create(ll_data_t data) {
    struct list_node *node = calloc(1, sizeof(struct list_node));
    node->data = data;
    return node;
}

struct list *list_create(void) { return calloc(1, sizeof(struct list)); }

size_t list_count(const struct list *list) {
    return list == NULL ? 0 : list->size;
}

void list_push(struct list *list, ll_data_t item_data) {
    if (list == NULL) {
        return;
    }

    struct list_node *node = list_node_create(item_data);

    if (list->last == NULL) {
        list->first = node;
    } else {
        node->prev = list->last;
        if (node->prev != NULL) {
            node->prev->next = node;
        }
    }

    list->last = node;
    list->size++;
}

ll_data_t list_pop(struct list *list) {
    if (list == NULL or list->size == 0) {
        return 0;
    }

    struct list_node *node = list->last;
    ll_data_t data = node->data;

    list->last = node->prev;
    if (list->last) {
        list->last->next = NULL;
    }

    list->size--;
    if (list->size == 0) {
        list->first = NULL;
        list->last = NULL;
    }

    free(node);
    return data;
}

void list_unshift(struct list *list, ll_data_t item_data) {
    if (list == NULL) {
        return;
    }

    struct list_node *node = list_node_create(item_data);

    if (list->first == NULL) {
        list->last = node;
    } else {
        node->next = list->first;
        if (node->next != NULL) {
            node->next->prev = node;
        }
    }

    list->first = node;
    list->size++;
}

ll_data_t list_shift(struct list *list) {
    if (list == NULL or list->size == 0) {
        return 0;
    }

    struct list_node *node = list->first;
    ll_data_t data = node->data;

    list->first = node->next;
    if (list->first) {
        list->first->prev = NULL;
    }

    list->size--;
    if (list->size == 0) {
        list->first = NULL;
        list->last = NULL;
    }

    free(node);
    return data;
}

void list_delete(struct list *list, ll_data_t data) {
    if (list == NULL) {
        return;
    }

    for (struct list_node *node = {list->first}; node != NULL;
         node = node->next) {
        if (node->data == data) {
            if (node->prev) {
                node->prev->next = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }

            list->size--;
            if (list->size == 0) {
                list->first = NULL;
                list->last = NULL;
            }

            if (list->first == node) {
                list->first = node->next;
            }
            if (list->last == node) {
                list->last = node->prev;
            }

            free(node);
            return;
        }
    }
}

void list_destroy(struct list *list) {
    if (list == NULL) {
        return;
    }

    while (list->size > 0) {
        list_pop(list);
    }
    free(list);
}
