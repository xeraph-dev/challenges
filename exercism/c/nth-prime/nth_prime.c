#include "nth_prime.h"

#include <iso646.h>
#include <stdbool.h>

static bool is_prime(uint64_t num) {
    if (num < 2)
        return false;
    if (num == 2 or num == 3)
        return true;
    if (num % 2 == 0 or num % 3 == 0)
        return false;

    for (uint64_t i = 5; i * i <= num; i += 2) {
        if (num % i == 0)
            return false;
    }

    return true;
}

uint32_t nth(uint32_t n) {
    if (n == 0)
        return 0;

    uint32_t prime = {2};

    while (--n) {
        prime = (prime == 2) ? 3 : prime + 2;
        while (not is_prime(prime))
            prime += 2;
    }

    return prime;
}
