#include "menu.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>
#include <cuttle/utils.h>

#include "color.h"
#include "graphics.h"
#include "error.h"

colored_string MENU[24];

void initialize_menu()
{
	memset(MENU, 0, sizeof(MENU));
}

void menu_line(int row, char *t, color c)
{
	strncpy(MENU[row].string, t, sizeof(MENU[row].string));
	MENU[row].c = c;
}

void draw_menu()
{
	for (int row = 0; row < 24; ++row) {
		draw_colored_string(MENU[row], 1, row + 1);
	}
}
