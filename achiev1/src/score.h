#ifndef _SCORE_H_
#define _SCORE_H_
#include "pattern.h"

extern int (*patterns[]) (int, int);
extern void (*print_patterns[]) ();
// Calculate score for each players
void score_calculation(int scores[]);

// Set all values of pattern_score to 0
void reset_pattern_score(int pattern_score[]);

// Return max of pattern score
int max_pattern_score(int pattern_score[]);

#endif // _SCORE_H_