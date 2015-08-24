#include "graphics.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "color.h"

colored_string HUD[2 * MAPVIEW_RADIUS_Y];
colored_string MESSAGES[5];
int MESSAGE_INDEX = 0;

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

void message_line(char *t, color c)
{
	if (MESSAGE_INDEX < 5) {
	strncpy(MESSAGES[MESSAGE_INDEX].string, t, sizeof(MESSAGES[MESSAGE_INDEX].string));
	MESSAGES[MESSAGE_INDEX].c = c;
	MESSAGE_INDEX++;
	} else {
		strncpy(MESSAGES[0].string, MESSAGES[1].string, sizeof(MESSAGES[0].string));
		MESSAGES[0].c = MESSAGES[1].c;

		strncpy(MESSAGES[1].string, MESSAGES[2].string, sizeof(MESSAGES[1].string));
		MESSAGES[1].c = MESSAGES[2].c;

		strncpy(MESSAGES[2].string, MESSAGES[3].string, sizeof(MESSAGES[2].string));
		MESSAGES[2].c = MESSAGES[3].c;

		strncpy(MESSAGES[3].string, MESSAGES[4].string, sizeof(MESSAGES[3].string));
		MESSAGES[3].c = MESSAGES[4].c;

		strncpy(MESSAGES[4].string, t, sizeof(MESSAGES[4].string));
		MESSAGES[4].c = c;
	}
}

void draw_messages()
{
	for (int row = 0; row < 5; ++row) {
		draw_colored_string(MESSAGES[row], 1, 2 * MAPVIEW_RADIUS_Y + 1 + row);
	}
}
