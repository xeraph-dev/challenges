#include "matching_brackets.h"

#include <iso646.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *prev;
} node_t;

static node_t *node_push(node_t *node, char data) {
    node_t *new_node = calloc(1, sizeof(node_t));
    new_node->data = data;
    new_node->prev = node;
    return new_node;
}

static bool node_match(node_t *node, char data) {
    if (node == NULL) {
        return false;
    } else {
        return (node->data == '[' and data == ']') or
               (node->data == '{' and data == '}') or
               (node->data == '(' and data == ')');
    }
}

static node_t *node_pop(node_t *node) {
    if (node == NULL) {
        return NULL;
    }
    node_t *prev = node->prev;
    free(node);
    return prev;
}

static void node_free(node_t *node) {
    while (node != NULL) {
        node = node_pop(node);
    }
}

bool is_paired(const char *input) {
    node_t *node = {0};
    for (const char *ch = {input}; *ch != '\0'; ch++) {
        if (*ch == '(' or *ch == '{' or *ch == '[') {
            node = node_push(node, *ch);
        } else if ((*ch == ')' or *ch == '}' or *ch == ']')) {
            if (node_match(node, *ch)) {
                node = node_pop(node);
            } else {
                goto end;
            }
        }
    }

    if (node != NULL) {
    end:
        node_free(node);
        node = NULL;
        return false;
    }

    return true;
}
