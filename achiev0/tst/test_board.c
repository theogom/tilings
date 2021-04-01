#include "../src/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TESTED FUNCTIONS/////////////////////////////////////////
/*

int opposite_dir(int dir);

int opposite_i(int i, int dir);

int opposite_j(int j, int dir);
*/
///////////////////////////////////////////////////////////

extern struct board b;
extern struct tile tile1;
extern int board_size;

void board_test()
{
    // Check if we get the correct opposite direction
    printf("TEST:opposite direction...");
    if ((opposite_dir(NORTH) != SOUTH) || (opposite_dir(SOUTH) != NORTH) || (opposite_dir(EAST) != WEST) || (opposite_dir(WEST) != EAST))
    {
        fprintf(stderr, "ERROR: Unable to get opposite direction\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check if we get the correct adjacent line index in a diraction
    printf("TEST:opposite i...");
    if ((opposite_i(1, NORTH) != 0) || (opposite_i(1, SOUTH) != 2) || (opposite_i(1, EAST) != 1) || (opposite_i(1, WEST) != 1))
    {
        fprintf(stderr, "ERROR: Unable to get adjacent line index in a diraction\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check if we get the correct adjacent column index in a diraction
    printf("TEST:opposite j...");
    if ((opposite_j(1, NORTH) != 1) || (opposite_j(1, SOUTH) != 1) || (opposite_j(1, EAST) != 2) || (opposite_j(1, WEST) != 0))
    {
        fprintf(stderr, "ERROR: Unable to get adjacent column index in a diraction\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check if the tile is correctly placed and if check_color_dir is correct
    change_board_tile_value(1, 1, &tile1);
    printf("TEST:check_color_dir...");
    if ((!check_color_dir(1, 1, NORTH,"RED")) || (!check_color_dir(1, 1, SOUTH,"BLUE")) || (!check_color_dir(1, 1, EAST,"RED")) || (!check_color_dir(1, 1, WEST,"RED")))
    {
        fprintf(stderr, "ERROR\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");

    // Check tile_owner set and get
    change_board_tile_owner(1, 1, 0);
    printf("TEST:check_color_dir...");
    if (tile_owner(1, 1) != 0)
    {
        fprintf(stderr, "ERROR\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");
    
    //check count of neighbor tile and neighbor valid tile
    change_board_tile_value(0, 1, &tile1);
    change_board_tile_value(2, 1, &tile1);
    change_board_tile_value(1, 0, &tile1);
    change_board_tile_value(1, 2, &tile1);

    printf("TEST:nb_neighbor_tile...");
    if (nb_neighbor_tile(1, 1) != 4)
    {
        fprintf(stderr, "ERROR\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");
    
    printf("TEST:nb_neighbor_valide_tile...");
    if (nb_neighbor_valide_tile(1, 1, board_tile(1, 1)) != 2)
    {
        fprintf(stderr, "ERROR\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");

    // test list_playable_tiles
    change_board_tile_value(2, 1, empty_tile());
    change_board_tile_value(1, 0, empty_tile());
    change_board_tile_value(1, 2, empty_tile());

    printf("TEST:list_playable_tiles...");
    int playable_tiles[board_size*board_size][2];
    int nb_playable_tiles = list_playable_tiles(playable_tiles, &tile1, 0);
    if ((nb_playable_tiles != 4) && (playable_tiles[0][0] != 0) && (playable_tiles[0][1] != 0) && (playable_tiles[1][0] != 0) && (playable_tiles[1][1] != 2) && (playable_tiles[2][0] != 1) && (playable_tiles[2][1] != 0) && (playable_tiles[3][0] != 1) && (playable_tiles[3][1] != 2))
    {
        fprintf(stderr, "ERROR\e[m\n");
    }
    printf("\e[32mSUCCEED\e[m\n");





}

int main(void)
{
    printf("\nPerforming board tests...\n");
    board_init();
    board_test();
    return EXIT_SUCCESS;
}