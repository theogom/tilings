#ifndef __PATTERN_H_
#define __PATTERN_H_
#include "board.h"
#define MAX_NB_PATTERN 20
#define NB_PATTERN 3

extern int board_size;

int pattern_1(int i, int j);
int pattern_2(int i, int j);
int pattern_3(int i, int j);

void print_all_patterns();

void print_pattern_1();
void print_pattern_2();
void print_pattern_3();

#endif // __PATTERN_H_