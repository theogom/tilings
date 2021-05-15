#ifndef __OPT_H_
#define __OPT_H_

// Define limit parameters

#define MIN_BOARD_SIZE 1
#define MAX_BOARD_SIZE 50

#define MIN_NB_PLAYER 2
#define MAX_NB_PLAYER 20

#define MAX_NB_COLOR 20

// Game parameters
extern int seed;
extern int board_size;
extern int nb_player;

// Function for parsing the options of the program
int parse_opts(int argc, char* argv[]);

#endif // __OPT_H_
