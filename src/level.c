#include "level.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "error.h"
#include "color.h"
#include "entity.h"
#include "graphics.h"
#include "enemy.h"
#include "dispatch_gen.h"

void __collide_door(level *l, int x, int y, entity *e)
{
	message_line("The door opens.", YELLOW);
	l->walls[x][y] = VOID;
}

tile TILES[TILE_INDEX_MARKER] = {
	{' ', {COLOR_BLACK, COLOR_BLACK}, 0, 1, NULL}, // void
	{'.', {COLOR_GREEN, COLOR_BLACK}, 1, 0, NULL}, // ground
	{'T', {COLOR_YELLOW, COLOR_GREEN}, 1, 0, NULL}, // tree
	{'.', {COLOR_WHITE, COLOR_BLACK}, 1, 0, NULL}, // stone_floor
	{'#', {COLOR_WHITE, COLOR_BLACK}, 1, 0, NULL}, // stone_wall
	{'+', {COLOR_YELLOW, COLOR_BLACK}, 1, 0, __collide_door}, // door
	{'.', {COLOR_YELLOW, COLOR_BLACK}, 1, 0, NULL}, // plaza
};

void load_level(level *l, char *dungeon, int x, int y)
{
	char path[100];
	sprintf(path, "dungeons/%s/%d_%d.lvl", dungeon, x, y);
	FILE *f = fopen(path, "rb");
	if (f == NULL) {
		dispatch_gen(l, x, y);
	} else {
		fread(l, 1, sizeof(level), f);
		fclose(f);
	}
}

void save_level(level *l, char *dungeon, int x, int y)
{
	char path[100];
	sprintf(path, "dungeons/%s/%d_%d.lvl", dungeon, x, y);
	FILE *f = fopen(path, "wb+");
	fwrite(l, 1, sizeof(level), f);
	fclose(f);
}

tile *get_wall_tile(level *l, int x, int y)
{
	return &TILES[l->walls[x][y]];
}

tile *get_floor_tile(level *l, int x, int y)
{
	return &TILES[l->floor[x][y]];
}

void draw_level(level *l, int camera_x, int camera_y)
{
	if (l != NULL) {
		for (int x = camera_x - MAPVIEW_RADIUS_X; x < camera_x + MAPVIEW_RADIUS_X; ++x) {
			for (int y = camera_y - MAPVIEW_RADIUS_Y; y < camera_y + MAPVIEW_RADIUS_Y; ++y) {
				if (!(x < 0 || y < 0 || x > LEVEL_DIM - 1 || y > LEVEL_DIM - 1)) {
					tile_index ti = l->walls[x][y];
					tile *t = &TILES[ti];
					if (ti != VOID) {
						draw_glyph(t->glyph, t->color, x - camera_x + MAPVIEW_RADIUS_X, y - camera_y + MAPVIEW_RADIUS_Y);
					} else {
						ti = l->floor[x][y];
						t = &TILES[ti];
						if (ti != VOID) {
							draw_glyph(t->glyph, t->color, x - camera_x + MAPVIEW_RADIUS_X, y - camera_y + MAPVIEW_RADIUS_Y);
						}
					}
					if (l->items[x][y].type != EMPTY_SLOT) {
						draw_glyph(l->items[x][y].glyph, YELLOW, x - camera_x + MAPVIEW_RADIUS_X, y - camera_y + MAPVIEW_RADIUS_Y);
					}
				}
			}
		}
		draw_enemies(l, camera_x, camera_y);
	}
}
