#include "entity.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "level.h"
#include "color.h"
#include "graphics.h"

void draw_entity(entity *e, int camera_x, int camera_y)
{
	if (e->x - camera_x + MAPVIEW_RADIUS_X < 2 * MAPVIEW_RADIUS_X
			&& e->y - camera_y + MAPVIEW_RADIUS_Y < 2 * MAPVIEW_RADIUS_Y) {
		draw_glyph(e->glyph, e->color, e->x - camera_x + MAPVIEW_RADIUS_X, e->y - camera_y + MAPVIEW_RADIUS_Y);
	}
}

static void move_entity_worker(entity *e, level *l, int tx, int ty) {
	if (tx >= 0 && ty >= 0 && tx < LEVEL_DIM && ty < LEVEL_DIM) {
		for (int i = 0; i < l->enemy_index; ++i) {
			char s[256];
			sprintf(s, "check: %d, %d | %d, %d | %p", l->enemies[i].x, l->enemies[i].y, tx, ty, l->enemies[i].collision_handler);
			hud_line(3, s, RED);
			if (l->enemies[i].x == tx && l->enemies[i].y == ty) {
				if (l->enemies[i].collision_handler != NULL) {
					l->enemies[i].collision_handler(l, e);
				}
				return;
			}
		}
		if (l->walls[tx][ty] == VOID) {
			e->x = tx;
			e->y = ty;
		} else {
			if (get_wall_tile(l, tx, ty)->collision_handler != NULL) {
				get_wall_tile(l, tx, ty)->collision_handler(l, tx, ty, e);
			}
		}
	} else {
		e->x = tx;
		e->y = ty;
	}
}

void move_entity_west(entity *e, level *l)
{
	move_entity_worker(e, l, e->x - 1, e->y);
}

void move_entity_east(entity *e, level *l)
{
	move_entity_worker(e, l, e->x + 1, e->y);
}

void move_entity_north(entity *e, level *l)
{
	move_entity_worker(e, l, e->x, e->y - 1);
}

void move_entity_south(entity *e, level *l)
{
	move_entity_worker(e, l, e->x, e->y + 1);
}
