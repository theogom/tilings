#include "game.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    game(argc, argv);       // Do a game
    print_all_patterns();   // Print available patterns
    display_results();      // Display the scoreboard
    print_board();	        // Print the final board
    free_all();             // Free all dynamically allocated memory
    return EXIT_SUCCESS;
}
