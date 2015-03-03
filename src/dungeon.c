#include "dungeon.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "level.h"
#include "color.h"
#include "graphics.h"

int universal_to_sector(int u)
{
	return u % LEVEL_DIM;
}
int sector_to_universal(int s, int sector_index)
{
	return s + (sector_index * LEVEL_DIM);
}

void load_dungeon(dungeon *d, char *name, int player_x, int player_y)
{
	if (name != NULL) {
		strncpy(d->name, name, sizeof(d->name));
	}
	d->player_x = player_x;
	d->player_y = player_y;
	char path[100];
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			int ax = d->player_x - 1 + x;
			int ay = d->player_y - 1 + y;
			sprintf(path, "dungeons/%s/%d_%d.lvl", d->name, ax, ay);
			load_level(&d->sectors[x][y], path);
		}
	}
}

void save_dungeon(dungeon *d)
{
	char path[100];
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			int ax = d->player_x - 1 + x;
			int ay = d->player_y - 1 + y;
			sprintf(path, "dungeons/%s/%d_%d.lvl", d->name, ax, ay);
			save_level(&d->sectors[x][y], path);
		}
	}
}

void move_player_dungeon(dungeon *d, int player_x, int player_y)
{
	save_dungeon(d);
	load_dungeon(d, NULL, player_x, player_y);
}

void draw_dungeon(dungeon *d, int camera_x, int camera_y)
{
	draw_level(&d->sectors[1][1], camera_x, camera_y); // center, and active

	draw_level(&d->sectors[0][0], camera_x + LEVEL_DIM, camera_y + LEVEL_DIM);
	draw_level(&d->sectors[1][0], camera_x, camera_y + LEVEL_DIM);
	draw_level(&d->sectors[2][0], camera_x - LEVEL_DIM, camera_y + LEVEL_DIM);
	draw_level(&d->sectors[0][1], camera_x + LEVEL_DIM, camera_y);
	draw_level(&d->sectors[2][1], camera_x - LEVEL_DIM, camera_y);
	draw_level(&d->sectors[0][2], camera_x + LEVEL_DIM, camera_y - LEVEL_DIM);
	draw_level(&d->sectors[1][2], camera_x, camera_y - LEVEL_DIM);
	draw_level(&d->sectors[2][2], camera_x - LEVEL_DIM, camera_y - LEVEL_DIM);
}
