#include "color.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

color WHITE = {COLOR_WHITE, COLOR_BLACK};
color RED = {COLOR_RED, COLOR_BLACK};
color GREEN = {COLOR_GREEN, COLOR_BLACK};
color BLUE = {COLOR_BLUE, COLOR_BLACK};
color YELLOW = {COLOR_YELLOW, COLOR_BLACK};

void initialize_color()
{
	start_color();
	short i, j;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			if (i > 0 || j > 0) {
				init_pair(i * 8 + j, j, i);
			}
		}
	}
}

void draw_glyph(char g, color c, int x, int y)
{
	mvaddch(y, x, g | COLOR_PAIR(c.bg * 8 + c.fg));
}

void draw_colored_string(colored_string s, int x, int y)
{
	move(y, x);
	int len = strlen(s.string);
	for (int i = 0; i < len; ++i) {
		addch(s.string[i] | COLOR_PAIR(s.c.bg * 8 + s.c.fg));
	}
}
