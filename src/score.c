#include "score.h"

const char *color_list[MAX_NB_COLOR];

void score_calculation(int scores[])
{
	int pattern_score[MAX_NB_PATTERN];
	fill_1D_int(0, MAX_NB_PATTERN, pattern_score);
	pattern_score_calculation(scores, pattern_score);
	color_area_score_calculation(scores);
}

void pattern_score_calculation(int scores[], int pattern_score[])
{
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
					scores[tile_owner(i, j)] += max(MAX_NB_PATTERN, pattern_score);
					fill_1D_int(0, MAX_NB_PATTERN, pattern_score);
				}
			}
		}
	}
}


int max(int len, int array[]) {
	int m = 0;
	for (int i = 0; i < len; ++i)
	{
		m = (m < array[i]) ? array[i] : m;
	}
	return m;
}

void color_area_score_calculation(int scores[])
{
	reset_color_list();
	list_colors();
	for (int c = 0; c < MAX_NB_COLOR; ++c)
	{
		if (color_list[c] == NULL)
		{
			break;
		}
		color_area_score_calculation_aux(color_list[c], scores);
	}
}

void color_area_score_calculation_aux(const char *color, int scores[])
{
	int nb_tile_owned[nb_player];
	int tiles_done[board_size][board_size];
	fill_2D_int(0, board_size, board_size, tiles_done);
	for (int i = 0; i < board_size; ++i)
	{ 
		for (int j = 0; j < board_size; ++j)
		{
			if (!tiles_done[i][j])
			{
				fill_1D_int(0, nb_player, nb_tile_owned);
				color_area_rec(color, i, j, tiles_done, nb_tile_owned);
				asign_color_area_score(nb_tile_owned, scores);
			}
		}
	}
}

void color_area_rec(const char *color, int i, int j, int tiles_done[][board_size], int nb_tile_owned[])
{
	if (color_is_in(color, i, j) && !tiles_done[i][j])
	{
		tiles_done[i][j] = 1;
		++nb_tile_owned[tile_owner(i, j)];
		for (int d = 0; d < MAX_DIRECTION; ++d)
		{
			if (check_color_dir(i, j, d, color) && check_color_dir(opposite_i(i, d), opposite_j(j, d), opposite_dir(d), color))
			{
				color_area_rec(color, opposite_i(i, d), opposite_j(j, d), tiles_done, nb_tile_owned);
			}
		}
	}
}

void asign_color_area_score(int nb_tile_owned[], int scores[])
{	
	int nb_max = 0;
	int p_max[nb_player];
	int m = max(nb_player, nb_tile_owned);
	int size = 0;
	for (int p = 0; p < nb_player; ++p)
	{
		size += nb_tile_owned[p];
		if (nb_tile_owned[p] == m)
		{
			p_max[nb_max++] = p;
		}
	}
	for (int i = 0; i < nb_max; ++i)
	{
		scores[p_max[i]] += size*size/nb_max;

	}
}

void fill_1D_int(int n, int len, int array[])
{
	for (int i = 0; i < len; ++i)
	{
		array[i] = n;
	}
}

void fill_2D_int(int n, int len1, int len2, int array[][len2])
{
	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			array[i][j] = n;
		}
	}
}

int color_index(const char *color) {
	for (int c = 0; c < MAX_NB_COLOR; ++c)
	{
		if (color_list[c] != NULL)
		{
			if (!strcmp(color_list[c], color))
			{
				return c;
			}
		}
	}
	return -1;
}

void reset_color_list()
{
	for (int i = 0; i < MAX_NB_COLOR; ++i)
	{
		color_list[i] = NULL;
	}
}

void insert_color(const char *color)
{	
	if (color_index(color) == -1)
	{
		for (int i = 0; i < MAX_NB_COLOR; ++i)
		{
			if (color_list[i] == NULL)
			{
				color_list[i] = color;
				break;
			}
		}
	}
}

void list_colors()
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (!tile_is_empty(board_tile(i, j)))
			{
				for (int d = 0; d < MAX_DIRECTION; ++d)
				{
					insert_color(color_name(tile_edge(board_tile(i, j), d)));
				}
			}
		}
	}
}