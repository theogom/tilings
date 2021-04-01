#include "project.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	game(argc, argv);  // Do a game
	display_results(); // Display the scoreboard
	print_board();	   // Print the final board
	free_all();		   // Free all dynamically allocated memory
	return EXIT_SUCCESS;
}