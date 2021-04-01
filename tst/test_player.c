#include "../src/tile.h"
#include "../src/file.h"
#include "../src/player.h"
#include "../src/free.h"
#include <stdio.h>
#include <stdlib.h>

//TESTED FUNCTIONS/////////////////////////////////////////
/*
void players_init();

void deck_init(struct deck *d);

void shuffle(struct deck *d, const struct tile *set[], int tile_remaining);

void split_deck(struct deck *d);
*/
///////////////////////////////////////////////////////////

extern int nb_player;
extern int nb_tile;

void player_test()
{
	// Check if all the players enter the file correctly
	printf("TEST: Players list initialization...");
	struct file *test_players = players_init();
	
	if (number_of_element_file(test_players) != nb_player)
	{
		free_file(test_players);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: Players list initialization failed\e[m\n");
		exit(EXIT_FAILURE);
	}
	printf("\e[32mSUCCEED\e[m\n");

	// Check if the deck is the correct size after initialization
	printf("TEST: Deck initialization...");
	struct deck test_deck;
	deck_init(&test_deck);
	if (number_of_tile_deck(&test_deck) != nb_tile)
	{
		free_file(test_players);
		printf("\e[31mFAILED\n");
		fprintf(stderr, "ERROR: Deck initialisation failed\e[m\n");
		exit(EXIT_FAILURE);
	}
	printf("\e[32mSUCCEED\e[m\n");

	// Check if each player has received the correct number of tiles after distribution
	printf("TEST: Tiles distribution...");
	split_deck(test_players, &test_deck);
	int nb_tile_to_give = nb_tile - nb_tile % nb_player;
	struct element *actual_element = top(test_players);
	const struct player *actual_player = player_from_element(actual_element);
	while (actual_element != NULL)
	{
		if (number_of_element_file(get_stack(actual_player)) != nb_tile_to_give / nb_player)
		{
			free_file(test_players);
			printf("\e[31mFAILED\n");
			fprintf(stderr, "ERROR: Tiles distribution failed\e[m\n");
			exit(EXIT_FAILURE);
		}
		actual_element = get_next_element(actual_element);
	}
	free_file(test_players);
	printf("\e[32mSUCCEED\e[m\n");
}

int main(void)
{
	printf("\nPerforming players tests...\n");
	player_test();
	return EXIT_SUCCESS;
}
