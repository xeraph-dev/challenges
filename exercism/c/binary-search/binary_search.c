#include "binary_search.h"

const int *binary_search(int value, const int *arr, size_t length) {
  if (length == 0)
    return NULL;

  if (length == 1) {
    if (value == *arr)
      return arr;
    else
      return NULL;
  }
  const size_t left_length = {length / 2};
  const size_t right_length = {length - left_length};

  const int *left_arr = {arr};
  const int *right_arr = {arr + left_length};

  const int *left = binary_search(value, left_arr, left_length);
  const int *right = binary_search(value, right_arr, right_length);

  if (left != NULL)
    return left;

  if (right != NULL)
    return right;

  return NULL;
}
