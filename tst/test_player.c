#include "tile.h"
#include "file.h"
#include "player.h"
#include "free.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

extern int nb_player;
extern int nb_tile;

struct file* players;
struct deck* deck;

static void setup(void) {
    players = players_init();
    deck = malloc(sizeof(*deck));
    deck_init(deck);
}

static void teardown(void) {
    free_file(players);
    free(deck);
}

// Check if all the players enter the file correctly
void test_players_init(void) {
    printf("%s", __func__);

    if (number_of_element_file(players) != nb_player)
        FAIL("Players list initialization failed");
}

// Check if the deck is the correct size after initialization
void test_deck_init(void) {
    printf("%s", __func__);

    if (number_of_tile_deck(deck) != nb_tile)
        FAIL("Deck initialisation failed");
}

// Check if each player has received the correct number of tiles after distribution
void test_distribution(void) {
    printf("%s", __func__);

    split_deck(players, deck);
    int nb_tile_to_give = nb_tile - nb_tile % nb_player;
    struct element* current_element = top(players);
    const struct player* current_player = player_from_element(current_element);

    while (current_element != NULL) {
        if (number_of_element_file(get_stack(current_player)) != nb_tile_to_give / nb_player)
            FAIL("Tiles distribution failed");
        current_element = get_next_element(current_element);
    }
}

int test_player_main(void) {
    TEST(test_players_init);
    TEST(test_deck_init);
    TEST(test_distribution);

    SUMMARY();

    return EXIT_SUCCESS;
}
