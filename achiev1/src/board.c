#include "board.h"
#include <stdio.h>
#include <string.h>

extern int board_size;

struct board
{
	const struct tile *tile[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int tile_owner[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; // -1 for unowned tiles
};

// The board
struct board b;

const struct tile *board_tile(int i, int j)
{
	return b.tile[i][j];
}

void change_board_tile_value(int i, int j, const struct tile *tile)
{
	b.tile[i][j] = tile;
}

void change_board_tile_owner(int i, int j, int player_index)
{
	b.tile_owner[i][j] = player_index;
}

int tile_owner(int i, int j)
{
	return b.tile_owner[i][j];
}

void board_init()
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			change_board_tile_value(i, j, empty_tile());
			change_board_tile_owner(i, j, -1);
		}
	}
}

int nb_neighbor_tile(int i, int j)
{
	int nb_nbr = 0;
	for (int d = 0; d < MAX_DIRECTION; ++d)
	{
		if (is_in_board(opposite_i(i, d), opposite_j(j, d)))
		{
			nb_nbr += !tile_is_empty(board_tile(opposite_i(i, d), opposite_j(j, d)));
		}
	}
	return nb_nbr;
}

int opposite_dir(int dir)
{	
	switch (dir)
	{
	case NORTH:
		return SOUTH;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case EAST:
		return WEST;
	default:
		return ERROR_DIRECTION;
	}
}

int check_color_dir(int i, int j, int dir, const char *color)
{
	if (!is_in_board(i, j) || tile_is_empty(board_tile(i, j)))
	{
		return 0;
	}
	return !strcmp(color_name(tile_edge(board_tile(i, j), dir)), color);
}

int neighbor_is_valide_tile(int i, int j, int p_dir, const struct tile *p_tile)
{
	return check_color_dir(i, j, opposite_dir(p_dir), color_name(tile_edge(p_tile, p_dir)));
}

int nb_neighbor_valide_tile(int i, int j, const struct tile *p_tile)
{
	int nb_valide_nbr = 0;
	for (int d = 0; d < MAX_DIRECTION; ++d)
	{
		nb_valide_nbr += neighbor_is_valide_tile(opposite_i(i, d), opposite_j(j, d), d, p_tile);
	}
	return nb_valide_nbr;
}

void print_board()
{
	const char *empty = "\e[0m";
	printf(" ______");
	for (int j = 1; j < board_size; ++j)
	{
		printf("_______");
	}
	printf("\n");
	for (int i = 0; i < board_size; ++i)
	{
		printf("|");
		for (int j = 0; j < board_size; ++j)
		{	
			const char *north = tile_is_empty(board_tile(i, j)) ? empty : color_cstring(tile_edge(board_tile(i, j), NORTH));
			printf("%s  %s  %s  |", empty, north, empty);
		}
		printf("\n|");
		for (int j = 0; j < board_size; ++j)
		{
			const char *east = tile_is_empty(board_tile(i, j)) ? empty : color_cstring(tile_edge(board_tile(i, j), EAST));
			const char *west = tile_is_empty(board_tile(i, j)) ? empty : color_cstring(tile_edge(board_tile(i, j), WEST));
			if (tile_owner(i, j) == -1)
			{
				printf("%s  %s  %s  %s|", west, empty, east, empty);
			}
			else if (tile_owner(i, j) + 1 < 10)
			{
				printf("%s  %s %d%s  %s|", west, empty, tile_owner(i, j) + 1, east, empty);
			}
			else
			{
				printf("%s  %s%d%s  %s|", west, empty, tile_owner(i, j) + 1, east, empty);
			}
		}
		printf("\n|");
		for (int j = 0; j < board_size; ++j)
		{
			const char *south = tile_is_empty(board_tile(i, j)) ? empty : color_cstring(tile_edge(board_tile(i, j), SOUTH));
			printf("%s__%s__%s__|", empty, south, empty);
		}
		printf("\n");
	}
}

int list_playable_tiles(int playable_tiles[][2], const struct tile *p_tile, int first)
{
	int nb_playable_tiles = 0;
	int nb_nbr;
	int nb_valide_nbr;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (tile_is_empty(board_tile(i, j)))
			{
				nb_nbr = nb_neighbor_tile(i, j);
				if (nb_nbr > 0 || first)
				{
					nb_valide_nbr = nb_neighbor_valide_tile(i, j, p_tile);
					if (nb_nbr == nb_valide_nbr)
					{
						playable_tiles[nb_playable_tiles][0] = i;
						playable_tiles[nb_playable_tiles][1] = j;
						++nb_playable_tiles;
					}
				}
			}
		}
	}
	return nb_playable_tiles;
}

void print_tile(const struct tile *tile)
{
	const char *empty = "\e[0m";
	const char *north = tile_is_empty(tile) ? empty : color_cstring(tile_edge(tile, NORTH));
	const char *east = tile_is_empty(tile) ? empty : color_cstring(tile_edge(tile, EAST));
	const char *west = tile_is_empty(tile) ? empty : color_cstring(tile_edge(tile, WEST));
	const char *south = tile_is_empty(tile) ? empty : color_cstring(tile_edge(tile, SOUTH));

	printf(" ______ \n");
	printf("|%s  %s  %s  |\n", empty, north, empty);
	printf("|%s  %s  %s  %s|\n", west, empty, east, empty);
	printf("|%s__%s__%s__|\n", empty, south, empty);
}

int is_valid(int i, int j)
{
	return nb_neighbor_tile(i, j) == nb_neighbor_valide_tile(i, j, board_tile(i, j));
}

int opposite_i(int i, int dir)
{
	i = (dir == NORTH) ? i-1 : i;
	i = (dir == SOUTH) ? i+1 : i;
	return i;
}

int opposite_j(int j, int dir)
{
	j = (dir == WEST) ? j-1 : j;
	j = (dir == EAST) ? j+1 : j;
	return j;
}

int is_in_board(int i, int j)
{
	return ((i >= 0) && (j >= 0) && (i < board_size) && (j < board_size));
}