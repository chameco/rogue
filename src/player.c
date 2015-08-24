#include "player.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "entity.h"
#include "item.h"
#include "graphics.h"
#include "dungeon.h"

entity PLAYER;

char *DISTURBANCE_TEXT[10] = {
	"nonexistent",
	"minor",
	"meh",
	"gettin' up there",
	"moderate",
	"unnerving",
	"dangerous",
	"I want my Mom",
	"9000",
	"9001",
};

void initialize_player()
{
	PLAYER.x = PLAYER.y = 0;
	PLAYER.glyph = '@';
	PLAYER.color.fg = COLOR_WHITE;
	PLAYER.color.bg = COLOR_BLACK;
	PLAYER.at = AI_NONE;
	PLAYER.stats[HP] = 10;
	PLAYER.stats[STR] = 0;
	PLAYER.stats[DEF] = 10;
	PLAYER.stats[DEX] = 0;
	make_item(&PLAYER.inventory[0], WINDENBO_BS);
	PLAYER.weapon_slot = 0;
}

void load_player()
{
	FILE *f = fopen("dungeons/overworld/player.dat", "r");
	if (f == NULL) {
		PLAYER.stats[HP] = -1;
	} else {
		fread(&PLAYER, sizeof(PLAYER), 1, f);
		fclose(f);
	}
}

void save_player()
{
	FILE *f = fopen("dungeons/overworld/player.dat", "w+");
	fwrite(&PLAYER, sizeof(PLAYER), 1, f);
	fclose(f);
}

entity *get_player()
{
	return &PLAYER;
}

void player_hud(dungeon *d)
{
	char sprintf_buffer[256];
	hud_line(0, PLAYER.name, WHITE);
	snprintf(sprintf_buffer, 256, "latitude: %d  longitude %d", d->player_x, d->player_y);
	hud_line(2, sprintf_buffer, WHITE);
	if (PLAYER.stats[DEX] < 0) PLAYER.stats[DEX] = 0;
	snprintf(sprintf_buffer, 256, "disturbance level: %s", DISTURBANCE_TEXT[PLAYER.stats[DEX]/10]);
	hud_line(3, sprintf_buffer, WHITE);
}
