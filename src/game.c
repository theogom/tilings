#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Global game variables
struct file* players;
int scores[MAX_NB_PLAYER];

// Display the results by counting the number of tiles remaining for each players
void display_results(void)
{
    score_calculation(scores);
    int max_score = 0; // Score of the current winner(s)
    int nb_winner = 0;
    int winners[nb_player]; // Array with the index of the winners
    const struct player* player = NULL;
    int player_id;
    struct element* actual_element = top(players);
    // Iterate through the file of players
    while (actual_element != NULL)
    {
        player = player_from_element(actual_element);
        player_id = get_id(player);
        if (scores[player_id] > max_score)
        {
            max_score = scores[player_id];
            // Reset the number of winner
            nb_winner = 1;
            winners[0] = player_id;
        }
        // A tie between players
        else if (scores[player_id] == max_score)
        {
            winners[nb_winner++] = player_id;
        }
        actual_element = get_next_element(actual_element);
    }
    // Print the score of all players
    printf("\nScoreboard :\n");
    for (int i = 0; i < nb_player; i++)
    {
        if (scores[i] == -1)
        {
            printf("- Player %d : %d\n", i + 1, 0);
            printf("Cheating is bad !\n");
        }
        else
        {
            printf("- Player %d : %d\n", i + 1, scores[i]);
        }
    }
    if (nb_winner == 1)
        printf("The winner is player %i, congratulations !\n", winners[0] + 1);
    else
    {
        printf("Oops there is a tie between multiple players\n");
        for (int p = 0; p < nb_winner; ++p)
        {
            printf("- Player %d wins\n", winners[p] + 1);
        }
    }
}

// Do a complete game
void game(int argc, char* argv[])
{
    if (parse_opts(argc, argv))
    {
        exit(EXIT_FAILURE);
    }
    printf("Seed : %d\n", seed);
    printf("Board size : %dx%d\n", board_size, board_size);
    printf("Number of players : %d\n", nb_player);
    srand(seed);

    int playable_tiles[board_size * board_size][2];
    int nb_playable_tiles;
    int nb_pass = 0; // Number of skipped turn
    int r = 0;
    // Deck initialization
    struct deck main_deck;
    deck_init(&main_deck);
    // Players initialization
    players = players_init();
    split_deck(players, &main_deck);
    // Board initialization
    board_init();
    int first_tile_placed = 0;
    int i;
    int j;
    for (int k = 0; k < nb_player; ++k)
    {
        scores[k] = 0;
    }
    // Iterate while all players have not skipped their turn
    while (nb_pass < nb_player)
    {
        // Get the top tile of the player who has to play
        const struct player* active_player = get_next_player(players);
        int player_id = get_id(active_player);
        struct file* player_stack = get_stack(active_player);
        struct element* active_element = top(player_stack);
        pop(player_stack);
        const struct tile* active_tile = tile_from_element(active_element);
        // List all the authorized places for the active tile
        (scores[player_id] == -1) ? (nb_playable_tiles = 0) : (nb_playable_tiles = list_playable_tiles(playable_tiles, active_tile, !first_tile_placed));
        // Check if the active player can play
        if (nb_playable_tiles == 0)
        {
            push(player_stack, active_element);
            nb_pass++;
        }
        else
        {
            nb_pass = 0;
            // Choose a place randomly between all available places
            r = randint(0, nb_playable_tiles - 1);
            i = playable_tiles[r][0];
            j = playable_tiles[r][1];
            change_board_tile_value(i, j, active_tile);
            change_board_tile_owner(i, j, player_id);
            // Check if the player cheated, if that's so, mark him as a cheater with score = -1
            if (!is_valid(i, j))
            {
                scores[player_id] = -1;
            }
            free(active_element);
            free_e++;
            // If a player has no tile remaining, game is over
            if (number_of_element_file(player_stack) == 0)
            {
                return;
            }
        }
        if (!first_tile_placed)
        {
            first_tile_placed = 1;
        }
    }
    return;
}
