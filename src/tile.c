#include "tile.h"
#include <string.h>

struct tile
{
  char *colors[MAX_DIRECTION]; // An array containging the tile colors name
};

//PARAMETERS//

// Create the different tiles
const struct tile empty_t = {.colors = {"EMPTY", "EMPTY", "EMPTY", "EMPTY"}};
const struct tile tile1 = {.colors = {"RED", "BLUE", "RED", "RED"}};
const struct tile tile2 = {.colors = {"BLUE", "RED", "WHITE", "RED"}};
const struct tile tile3 = {.colors = {"RED", "BLUE", "RED", "WHITE"}};

// Initialize the differents pairs for the deck
int pair_number = 3;
int nb_tile = 100; // Constant for test purpose
struct deck_pair pairs[] = {{.t = &tile1, .n = 40}, {.t = &tile2, .n = 30}, {.t = &tile3, .n = 30}};

//FUNCTIONS//

// A tile that is empty
const struct tile *empty_tile(void)
{
  return (&empty_t);
}

// A predicate telling if the tile is empty
int tile_is_empty(const struct tile *t)
{
  return (t == empty_tile());
}

// A comparator between tiles
int tile_equals(const struct tile *t1, const struct tile *t2)
{
  for (int i = 0; i < MAX_DIRECTION; i++)
  {
    if (strcmp(t1->colors[i], t2->colors[i]))
    {
      return 0;
    }
  }
  return 1;
}

// Accessors to the color of the edges
struct color *tile_edge(const struct tile *t, enum direction d)
{
  return color_from_name(t->colors[d]);
}

// A function that fills a deck with tiles
void deck_init(struct deck *d)
{
  d->size = pair_number;
  for (int i = 0; i < pair_number; i++)
  {
    d->cards[i].t = pairs[i].t;
    d->cards[i].n = pairs[i].n;
  }
}
