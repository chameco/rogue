#include "entity.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "enemy.h"
#include "dungeon.h"
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

bool move_entity_worker(entity *e, dungeon *d, int tx, int ty) {
	level *l;
	if (tx >= 0 && ty >= 0 && tx < LEVEL_DIM && ty < LEVEL_DIM) {
		l = &(d->sectors[1][1]);
		if (collide_enemies(l, e, tx, ty)) return false;
		if (l->walls[tx][ty] == VOID) {
			e->x = tx;
			e->y = ty;
		} else {
			if (get_wall_tile(l, tx, ty)->collision_handler != NULL) {
				get_wall_tile(l, tx, ty)->collision_handler(l, tx, ty, e);
			}
		}
	} else {
		if (tx < 0) {
			l = &(d->sectors[0][1]);
			tx = LEVEL_DIM - 1;
		} else if (tx >= LEVEL_DIM) {
			l = &(d->sectors[2][1]);
			tx = 0;
		}
		if (ty < 0) {
			l = &(d->sectors[1][0]);
			ty = LEVEL_DIM - 1;
		} else if (ty >= LEVEL_DIM) {
			l = &(d->sectors[1][2]);
			ty = 0;
		}
		if (collide_enemies(l, e, tx, ty)) return false;
		if (l->walls[tx][ty] == VOID) {
			e->x = tx;
			e->y = ty;
			return true;
		} else {
			if (get_wall_tile(l, tx, ty)->collision_handler != NULL) {
				get_wall_tile(l, tx, ty)->collision_handler(l, tx, ty, e);
			}
		}
	}
	return false;
}

bool move_entity_west(entity *e, dungeon *l)
{
	return move_entity_worker(e, l, e->x - 1, e->y);
}

bool move_entity_east(entity *e, dungeon *l)
{
	return move_entity_worker(e, l, e->x + 1, e->y);
}

bool move_entity_north(entity *e, dungeon *l)
{
	return move_entity_worker(e, l, e->x, e->y - 1);
}

bool move_entity_south(entity *e, dungeon *l)
{
	return move_entity_worker(e, l, e->x, e->y + 1);
}
