#include "player.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "entity.h"

entity PLAYER;

void initialize_player()
{
	PLAYER.x = PLAYER.y = 0;
	PLAYER.glyph = '@';
	PLAYER.color.fg = COLOR_WHITE;
	PLAYER.color.bg = COLOR_BLACK;
	PLAYER.at = AI_NONE;
}

entity *get_player()
{
	return &PLAYER;
}
