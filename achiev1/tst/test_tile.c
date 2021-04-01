#include <stdlib.h>
#include <stdio.h>
#include "../src/tile.h"

extern struct tile tile1;
extern struct tile tile2;

//TESTED FUNCTIONS/////////////////////////////////////////
/*
const struct tile *empty_tile(void);

int tile_is_empty(const struct tile *t);

int tile_equals(const struct tile *t1, const struct tile* t2);

struct color* tile_edge(const struct tile *t, enum direction d);
*/
///////////////////////////////////////////////////////////

void tile_test()
{
  // Check if tiles are empty
  printf("TEST: Checking if tile is empty...");
  if (!(tile_is_empty(empty_tile()) && !tile_is_empty(&tile1)))
  {
    printf("\e[31mFAILED\n");
    fprintf(stderr, "ERROR: Empty check failed\e[m\n");
    exit(EXIT_FAILURE);
  }
  printf("\e[32mSUCCEED\e[m\n");

  // Check if tiles are equals
  printf("TEST: Checking if tiles are equals...");
  if (!tile_equals(&tile1, &tile1) || tile_equals(&tile1, &tile2))
  {
    printf("\e[31mFAILED\n");
    fprintf(stderr, "ERROR: Equality check failed\e[m\n");
    exit(EXIT_FAILURE);
  }
  printf("\e[32mSUCCEED\e[m\n");

  // Check if we correctly get the color of the edges
  printf("TEST: Getting the color of the edge...");
  if (tile_edge(&tile1, SOUTH) != color_from_name("BLUE") || tile_edge(&tile1, WEST) != color_from_name("RED"))
  {
    printf("\e[31mFAILED\n");
    fprintf(stderr, "ERROR: Unable to get edge color\e[m\n");
    exit(EXIT_FAILURE);
  }
  printf("\e[32mSUCCEED\e[m\n");
}

int main(void)
{
  printf("\nPerforming tiles tests...\n");
  tile_test();
  return EXIT_SUCCESS;
}
