#include "player.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "entity.h"

entity player;

void initialize_player()
{
	player.x = player.y = 0;
	player.glyph = '@';
	player.color.fg = COLOR_WHITE;
	player.color.bg = COLOR_BLACK;
}

entity *get_player()
{
	return &player;
}
