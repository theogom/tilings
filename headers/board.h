#ifndef __BOARD_H_
#define __BOARD_H_

#include "opt.h"
#include "tile.h"

extern int board_size;

struct board; // Anonymous struct for the board

// Initialise the board
void board_init(void);

// Place the tile on the board
void change_board_tile_value(int i, int j, const struct tile* tile);

// Change the owner of a tile on the board
void change_board_tile_owner(int i, int j, int player_index);

// Return tile's owner
int tile_owner(int i, int j);

// Return tile from index in board
const struct tile* board_tile(int i, int j);

// Count not empty neighbor tile
int nb_neighbor_tile(int i, int j);

// Return oposite direction
int opposite_dir(int dir);

// Return line index of the adjacent tile in dir direction
int opposite_i(int i, int dir);

// Return column index of the adjacent tile in dir direction
int opposite_j(int j, int dir);

// Check if tile (i, j) is in the board
int is_in_board(int i, int j);

// Check if the color on dir in board[i][j] correspond to color
int check_color_dir(int i, int j, int dir, const char* color);

// Test if is corresponding neighbor tile
int neighbor_is_valide_tile(int i, int j, int p_dir, const struct tile* p_tile);

// Count corresponding neighbor tile
int nb_neighbor_valide_tile(int i, int j, const struct tile* p_tile);

// Print the whole board with tiles
void print_board(void);

// Count the number of places available for the tile provided
int list_playable_tiles(int playable_tiles[][2], const struct tile* p_tile, int first);

// Print a tile with its colors
void print_tile(const struct tile* tile);

// Verify if the tile is valid
int is_valid(int i, int j);

// Check if the tile contain color
int color_is_in(const char* color, int i, int j);

#endif // __BOARD_H_