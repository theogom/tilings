#include "../src/game.h"
#include "../src/free.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//TESTED FUNCTIONS/////////////////////////////////////////
/*
void free_all();
*/
///////////////////////////////////////////////////////////

extern int free_f;
extern int free_e;
extern int free_p;
extern int nb_player;
extern int nb_tile;

char *argv[] = {"./project"};

void free_test()
{
    // Do a game loop first to allocate the memory
    // Suppress standard output of game()
    int stdout_copy = dup(1);
    fclose(stdout);
    game(1, argv);
    // Resume standard output
    stdout = fdopen(stdout_copy, "w");
    free_all();
    
    // Search for memory leak
    fprintf(stdout, "TEST: Checking if all allocated memory has been freed correctly...");
    int nb_tile_to_give = nb_tile - nb_tile % nb_player;
    if (free_f != nb_player + 1 || free_e != nb_tile_to_give + nb_player || free_p != nb_player)
    {
        fprintf(stdout, "\e[31mFAILED\n");
        fprintf(stderr, "ERROR: All allocated memory has not been freed correctly\e[m\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "\e[32mSUCCEED\e[m\n");
}

int main(void)
{
    printf("\nPerforming memory test...\n");
    free_test();
    return EXIT_SUCCESS;
}