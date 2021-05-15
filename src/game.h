#ifndef __GAME_H_
#define __GAME_H_

#include "opt.h"
#include "board.h"
#include "player.h"
#include "score.h"

// Counter for memory debugging and testing
extern int free_e;

// Display the results by counting the number of tiles remaining for each players
void display_results(void);

// Do a complete game
void game(int argc, char* argv[]);

#endif // __GAME_H_
