#include "color.h"
#include <string.h>
#define NB_COLOR 9

enum color_num
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	EMPTY
};

struct color
{
	int color_value;
	char *color_name;
	char *color_ansi;
};


// Current colors
;
struct color black = {BLACK, "BLACK", "\e[40m"};
struct color red = {RED, "RED", "\e[41m"};
struct color green = {GREEN, "GREEN", "\e[42m"};
struct color yellow = {YELLOW, "YELLOW", "\e[43m"};
struct color blue = {BLUE, "BLUE", "\e[44m"};
struct color magenta = {MAGENTA, "MAGENTA", "\e[45m"};
struct color cyan = {CYAN, "CYAN", "\e[46m"};
struct color white = {WHITE, "WHITE", "\e[47m"};
struct color empty = {EMPTY, "EMPTY", "\e[0m"};

struct color *colors[] = {
	&black,
	&red,
	&green,
	&yellow,
	&blue,
	&magenta,
	&cyan,
	&white,
	&empty
};

// A string giving the color name
const char *color_name(const struct color *t)
{
	return t->color_name;
}

// An ANSI-colored string describing the color
const char *color_cstring(const struct color *t)
{
	return t->color_ansi;
}

// Return a color from its name, or NULL
struct color *color_from_name(const char *name)
{
	for (int c = 0; c < NB_COLOR; ++c)
	{
		if (!strcmp(color_name(colors[c]), name))
		{
			return colors[c];
		}
	}
	return NULL;
}