#include "tests.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct board b;
extern struct tile tile1;
extern int board_size;


static void setup(void) {
    board_init();
    change_board_tile_value(0, 1, &tile1);
    change_board_tile_value(1, 0, &tile1);
    change_board_tile_value(1, 1, &tile1);
    change_board_tile_value(1, 2, &tile1);
    change_board_tile_value(2, 1, &tile1);
}

static void teardown(void) {
    return;
}

// Check if we get the correct opposite direction
void test_opposite_dir(void) {
    printf("%s", __func__);

    if ((opposite_dir(NORTH) != SOUTH) || (opposite_dir(SOUTH) != NORTH) || (opposite_dir(EAST) != WEST) ||
        (opposite_dir(WEST) != EAST))
        FAIL("Unable to get opposite direction");
}

// Check if we get the correct adjacent line index in a diraction
void test_opposite_i(void) {
    printf("%s", __func__);

    if ((opposite_i(1, NORTH) != 0) || (opposite_i(1, SOUTH) != 2) || (opposite_i(1, EAST) != 1) ||
        (opposite_i(1, WEST) != 1))
        FAIL("Unable to get adjacent line index in a direction");
}

// Check if we get the correct adjacent column index in a diraction
void test_opposite_j(void) {
    printf("%s", __func__);

    if ((opposite_j(1, NORTH) != 1) || (opposite_j(1, SOUTH) != 1) || (opposite_j(1, EAST) != 2) ||
        (opposite_j(1, WEST) != 0))
        FAIL("Unable to get adjacent column index in a diraction");
}

// Check if the tile is correctly placed and if check_color_dir is correct
void test_check_color_dir(void) {
    printf("%s", __func__);

    if ((!check_color_dir(1, 1, NORTH, "RED")) || (!check_color_dir(1, 1, SOUTH, "BLUE")) ||
        (!check_color_dir(1, 1, EAST, "RED")) || (!check_color_dir(1, 1, WEST, "RED")))
        FAIL("check_color_dir failed");
}

// Check tile_owner set and get
void test_tile_owner(void) {
    printf("%s", __func__);

    change_board_tile_owner(1, 1, 0);

    if (tile_owner(1, 1) != 0)
        FAIL("Tile owner failed");
}

// Check count of neighbor tile and neighbor valid tile
void test_neighbor_nb(void) {
    printf("%s", __func__);

    if (nb_neighbor_tile(1, 1) != 4)
        FAIL("Incorrect number of neighbor tiles");
}

void test_neighbor_valid_tile(void) {
    printf("%s", __func__);

    if (nb_neighbor_valide_tile(1, 1, board_tile(1, 1)) != 2)
        FAIL("Incorrect number of valid neighbor tiles");
}

// Test list_playable_tiles
void test_playable_tiles(void) {
    printf("%s", __func__);

    change_board_tile_value(2, 1, empty_tile());
    change_board_tile_value(1, 0, empty_tile());
    change_board_tile_value(1, 2, empty_tile());
    int playable_tiles[board_size * board_size][2];
    size_t nb_playable_tiles = list_playable_tiles(playable_tiles, &tile1, 0);

    if ((nb_playable_tiles != 4) && (playable_tiles[0][0] != 0) && (playable_tiles[0][1] != 0) &&
        (playable_tiles[1][0] != 0) && (playable_tiles[1][1] != 2) && (playable_tiles[2][0] != 1) &&
        (playable_tiles[2][1] != 0) && (playable_tiles[3][0] != 1) && (playable_tiles[3][1] != 2))
        FAIL("");
}

int test_board_main(void) {
    TEST(test_opposite_dir);
    TEST(test_opposite_i);
    TEST(test_opposite_j);
    TEST(test_check_color_dir);
    TEST(test_tile_owner);
    TEST(test_neighbor_nb);
    TEST(test_neighbor_valid_tile);
    TEST(test_playable_tiles);

    SUMMARY();

    return EXIT_SUCCESS;
}
