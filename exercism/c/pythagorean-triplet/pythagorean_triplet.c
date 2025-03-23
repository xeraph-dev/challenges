#include "pythagorean_triplet.h"

#include <stdlib.h>

triplets_t *triplets_with_sum(uint16_t sum) {
    triplets_t *triplets = malloc(sizeof(triplets_t));
    triplets->count = 0;

    for (uint16_t a = {1}; a < (sum / 3); a++) {
	for (uint16_t b = {a + 1}; b < (sum / 2); b++) {
	    uint16_t c = {sum - a - b};
	    if ((a*a + b*b) == c*c) {
		triplets = realloc(triplets, sizeof(triplets_t) + ((triplets->count + 1) * sizeof(triplet_t)));
		triplets->triplets[triplets->count++] = (triplet_t){a, b, c};
	    }
	}
    }
    
    return triplets;
}

void free_triplets(triplets_t *triplets) { free(triplets); }
