#include "score.h"

void score_calculation(int scores[])
{
	int pattern_score[MAX_NB_PATTERN];
	reset_pattern_score(pattern_score);
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (tile_owner(i, j) != -1)
			{
				if (scores[tile_owner(i, j)] != -1)
				{
					for (int p = 0; p < NB_PATTERN; ++p)
					{
						pattern_score[p] = patterns[p](i, j);
					}
					scores[tile_owner(i, j)] += max_pattern_score(pattern_score);
					reset_pattern_score(pattern_score);
				}
			}
		}
	}
}

void reset_pattern_score(int pattern_score[]) {
	for (int i = 0; i < MAX_NB_PATTERN; ++i)
	{
		pattern_score[i] = 0;
	}
}

int max_pattern_score(int pattern_score[]) {
	int max = 0;
	for (int i = 0; i < MAX_NB_PATTERN; ++i)
	{
		max = (max < pattern_score[i]) ? pattern_score[i] : max;
	}
	return max;
}