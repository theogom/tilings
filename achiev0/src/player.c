#include "player.h"
#include <stdio.h>
#include <stdlib.h>

struct player
{
    struct file *stack;
    int id;
};

// Return an integer in the range [low, high]
int randint(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

// Get the total amount of tiles in a deck
int number_of_tile_deck(struct deck *d)
{
    int count_tile = 0;
    // Sum the amount of tile in each card
    for (unsigned int i = 0; i < d->size; i++)
    {
        count_tile += d->cards[i].n;
    }
    return count_tile;
}

// A function that fills a file with players
struct file *players_init(void)
{
    // Initialize the players' list
    struct file *players = file_init();

    // Initialize players with an empty stack
    for (int i = 0; i < nb_player; i++)
    {
        // Initialize the stack
        struct file *f = file_init();
        // Initialize the player
        struct player *p = malloc(sizeof(struct player));
        p->stack = f;
        p->id = i;
        // Initialize the element
        struct element *player_to_push = create_element();
        set_data(player_to_push, p);
        // Push the player into the file
        push(players, player_to_push);
    }
    return players;
}

// Shuffle a deck of tile
void shuffle(struct deck *d, const struct tile *set[], int tile_remaining)
{
    int counter;
    int card_index;
    int rand_index;
    while (tile_remaining > 0)
    {
        counter = -1;
        card_index = 0;
        // Generate a random tile index
        rand_index = randint(0, tile_remaining - 1);
        // Go through the deck until we find our random tile
        while (counter < rand_index)
        {
            counter += d->cards[card_index++].n;
        }
        set[--tile_remaining] = d->cards[card_index - 1].t;
        // Remove the tile from the deck
        d->cards[card_index - 1].n--;
    }
}

// Distribute the tiles in the original deck equitably between the players
void split_deck(struct file *players_file, struct deck *d)
{
    // Find the number of tiles to distribute to each players
    int nb_tile = number_of_tile_deck(d);
    // Adapt this number so that each players can have the same number of tiles
    int nb_tile_to_give = nb_tile - nb_tile % nb_player;
    if (nb_tile_to_give == 0)
    {
        fprintf(stderr, "ERROR: Not enough tiles for the number of players\n");
        exit(EXIT_FAILURE);
    }

    // Shuffle the tiles and put them in a set of tile
    const struct tile *set[nb_tile_to_give];
    shuffle(d, set, nb_tile_to_give);

    // Distribution
    struct element *actual_element = top(players_file);
    const struct player *actual_player = player_from_element(actual_element);
    int index = 0;
    while (index < nb_tile_to_give)
    {
        struct element *tile_to_push = create_element();
        set_data(tile_to_push, set[index++]);
        // Push the tile into the player stack
        push(get_stack(actual_player), tile_to_push);
        (get_next_element(actual_element) == NULL) ? (actual_element = top(players_file)) : (actual_element = get_next_element(actual_element));
        actual_player = player_from_element(actual_element);
    }
}

// Get the next player in the game loop and add it at the end of the file
const struct player *get_next_player(struct file *players_file)
{
    struct element *actual_player = top(players_file);
    pop(players_file);
    push(players_file, actual_player);
    return player_from_element(actual_player);
}

// Get player's stack of tiles
struct file *get_stack(const struct player *p)
{
    return p->stack;
}

// Get player's unique identifier
int get_id(const struct player *p)
{
    return p->id;
}

// Return the player stored in the element
const struct player *player_from_element(struct element *e)
{
    return get_element_data(e);
}

// Return the tile stored in the element
const struct tile *tile_from_element(struct element *e)
{
    return get_element_data(e);
}