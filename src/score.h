#ifndef _SCORE_H_
#define _SCORE_H_
#include "pattern.h"
#include "board.h"
#include "opt.h"
#include "player.h"

extern int (*patterns[]) (int, int);

// Calculate score for each players
void score_calculation(int scores[]);

// Calculate score for each players of patterns
void pattern_score_calculation(int scores[], int pattern_score[]);

// Return max of int array
int max(int len, int array[]);

// Calculate score for each players of color area
void color_area_score_calculation(int scores[]);

// Construct all areas wich correspond to the given color
void color_area_score_calculation_aux(const char *color, int scores[]);

// Create recursively the area
void color_area_rec(const char *color, int i, int j, int tiles_done[][board_size], int nb_tile_owned[]);

// Asigne the right score of the current area to right players
void asign_color_area_score(int nb_tile_owned[], int scores[]);

// fill 1D array of integer with the value of n
void fill_1D_int(int n, int len, int array[]);

// fill DD array of integer with the value of n
void fill_2D_int(int n, int len1, int len2, int array[][len2]);

// Return index of color in color_list or -1 if color is not in color_list
int color_index(const char *color);

// Set all pointer in color_list to NULL
void reset_color_list(void);

// Insert a color in color_list
void insert_color(const char *color);

// Construct list of colors on the board
void list_colors(void);

#endif // _SCORE_H_
