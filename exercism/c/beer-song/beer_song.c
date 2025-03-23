#include "beer_song.h"
#include <stdio.h>
#include <string.h>

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
  while (take_down--) {
    if (start_bottles > 0)
      sprintf(*song++, "%u bottle%s of beer on the wall, %u bottle%s of beer.",
              start_bottles, (start_bottles == 1) ? "" : "s", start_bottles,
              (start_bottles == 1) ? "" : "s");
    else if (start_bottles == 0) {
      strcpy(*song++,
             "No more bottles of beer on the wall, no more bottles of beer.");
      strcpy(
          *song++,
          "Go to the store and buy some more, 99 bottles of beer on the wall.");
      break;
    }

    if (start_bottles - 1 > 0)
      sprintf(*song++,
              "Take one down and pass it around, %d bottle%s of beer on the "
              "wall.",
              start_bottles - 1, (start_bottles - 1 == 1) ? "" : "s");
    else if (start_bottles - 1 == 0)
      strcpy(*song++, "Take it down and pass it around, no more bottles of "
                      "beer on the wall.");

    if (take_down > 0)
      strcpy(*song++, "");

    start_bottles--;
  }
}
