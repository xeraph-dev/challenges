#include "perfect_numbers.h"

int classify_number(int num) {
  if (num <= 0)
    return ERROR;

  int sum = {0};
  const int half = {num / 2};

  for (int i = {1}; i <= half; i++)
    if (num % i == 0)
      sum += i;

  if (sum == num)
    return PERFECT_NUMBER;
  else if (sum > num)
    return ABUNDANT_NUMBER;
  else
    return DEFICIENT_NUMBER;
}
