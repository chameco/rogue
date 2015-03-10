#include "level.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "color.h"
#include "entity.h"
#include "graphics.h"

#include "gen_jungle.h"
#include "gen_city.h"

void __collide_door(level *l, int x, int y, entity *e)
{
	message_line(1, "The door opens.", YELLOW);
	l->walls[x][y] = VOID;
}

tile TILES[256] = {
	{' ', {COLOR_BLACK, COLOR_BLACK}, false, true, NULL}, // void
	{'.', {COLOR_GREEN, COLOR_BLACK}, true, false, NULL}, // ground
	{'T', {COLOR_YELLOW, COLOR_GREEN}, true, false, NULL}, // tree
	{'.', {COLOR_WHITE, COLOR_BLACK}, true, false, NULL}, // stone_floor
	{'#', {COLOR_WHITE, COLOR_BLACK}, true, false, NULL}, // stone_wall
	{'+', {COLOR_YELLOW, COLOR_BLACK}, true, false, __collide_door} // door
};

void load_level(level *l, char *p)
{
	FILE *f = fopen(p, "r");
	if (f == NULL) {
		//memset(l, VOID, sizeof(level));
		__gen_city(l);
	} else {
		fread(l, sizeof(level), 1, f);
		fclose(f);
	}
}

void save_level(level *l, char *p)
{
	FILE *f = fopen(p, "w+");
	fwrite(l, sizeof(level), 1, f);
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
				}
			}
		}
	}
}
