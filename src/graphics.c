#include "graphics.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>
#include <cuttle/utils.h>

#include "color.h"

colored_string HUD[2 * MAPVIEW_RADIUS_Y];
colored_string MESSAGES[24 - (2 * MAPVIEW_RADIUS_Y + 1)];

void initialize_graphics()
{
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	initialize_color();

	memset(HUD, 0, sizeof(HUD));
	memset(MESSAGES, 0, sizeof(MESSAGES));
}

void finalize_graphics()
{
	endwin();
}

void hud_line(int row, char *t, color c)
{
	strncpy(HUD[row].string, t, sizeof(HUD[row].string));
	HUD[row].c = c;
}

void draw_hud()
{
	for (int row = 0; row < 2 * MAPVIEW_RADIUS_Y; ++row) {
		draw_colored_string(HUD[row], 2 * MAPVIEW_RADIUS_X + 1, row);
	}
}

void message_line(int row, char *t, color c)
{
	strncpy(MESSAGES[row].string, t, sizeof(MESSAGES[row].string));
	MESSAGES[row].c = c;
}

void draw_messages()
{
	for (int row = 0; row < 24 - (2 * MAPVIEW_RADIUS_Y + 1); ++row) {
		draw_colored_string(MESSAGES[row], 1, 2 * MAPVIEW_RADIUS_Y + 1 + row);
	}
}
