#include "armstrong_numbers.h"
#include <math.h>
#include <stdio.h>

bool is_armstrong_number(int candidate) {
  int len = {1};
  for (int i = {candidate}; i >= 10; i /= 10, len++)
    ;

  int sum = {0};

  for (int i = {candidate}; i > 0; i /= 10)
    sum += pow(i % 10, len);

  return sum == candidate;
}
