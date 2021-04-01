#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "tile.h"
#include "file.h"

extern int nb_player;

// Anonymous struct for player
struct player;

// A function that fills a file with players
struct file *players_init(void);

// Return an integer in the range [low, high]
int randint(int low, int high);

// Get the total amount of tiles in a deck
int number_of_tile_deck(struct deck *d);

// Shuffle a deck of tile
void shuffle(struct deck *d, const struct tile *set[], int tile_remaining);

// Distribute the tiles in the original deck equitably between the players
void split_deck(struct file *players_file, struct deck *d);

// Get the next player in the game loop
const struct player *get_next_player(struct file *players_file);

// Get player's stack of tiles
struct file *get_stack(const struct player *p);

// Get player's unique identifier
int get_id(const struct player *p);

// Return the player stored in the element
const struct player *player_from_element(struct element *e);

// Return the tile stored in the element
const struct tile *tile_from_element(struct element *e);

#endif // __PLAYER_H_
