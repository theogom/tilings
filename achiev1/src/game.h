#ifndef __GAME_H_
#define __GAME_H_

#include "board.h"
#include "player.h"
#include "score.h"

// Counter for memory debugging and testing
extern int free_e;

// Display the results of the game (score & winner(s))
void display_results(void);

// Do a complete game
void game(int argc, char *argv[]);

#endif // __GAME_H_