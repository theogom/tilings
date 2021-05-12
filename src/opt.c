#include "opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// Initialize default parameters if they are not specified by the user
int seed = 11098;
int nb_player = 3;
int board_size = 10;

// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
// -b <board size> : sets the board size
// -n <number of players> : sets the number of players
int parse_opts(int argc, char* argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "s:b:n:")) != -1)
    {
        switch (opt)
        {
        case 's':
            seed = atoi(optarg);
            break;
        case 'b':
            board_size = atoi(optarg);
            break;
        case 'n':
            nb_player = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-s seed] [-b board_size] [-n number_of_players] \n", argv[0]);
            return EXIT_FAILURE;
        }
        if ((board_size < MIN_BOARD_SIZE) || (board_size > MAX_BOARD_SIZE))
        {
            fprintf(stderr, "Board size must be between %d and %d\n", MIN_BOARD_SIZE, MAX_BOARD_SIZE);
            return EXIT_FAILURE;
        }
        if ((nb_player < MIN_NB_PLAYER) || (nb_player > MAX_NB_PLAYER))
        {
            fprintf(stderr, "Number of players must be between %d and %d\n", MIN_NB_PLAYER, MAX_NB_PLAYER);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
