#include "enemy.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "entity.h"
#include "level.h"
#include "dungeon.h"

void __ai_none(dungeon *d, int x, int y, entity * e)
{
}

void __ai_random_walk(dungeon *d, int x, int y, entity *e)
{
	int dir = rand() % 4;
	switch (dir) {
		case 0:
			move_entity_north(e, d);
			break;
		case 1:
			move_entity_south(e, d);
			break;
		case 2:
			move_entity_west(e, d);
			break;
		case 3:
			move_entity_east(e, d);
			break;
	}
}

void (*AI_HANDLERS[AI_SUBTYPES])(dungeon *d, int x, int y, entity *e) = {
	__ai_none,
	__ai_random_walk,
};

bool collide_enemies(level *l, entity *e, int x, int y)
{
	for (int i = 0; i < l->enemy_index; ++i) {
		if (l->enemies[i].x == x && l->enemies[i].y == y) {
			if (l->enemies[i].collision_handler != NULL) {
				l->enemies[i].collision_handler(l, &l->enemies[i], e);
			}
			return true;
		}
	}
	return false;
}

void update_enemies(dungeon *d, int x, int y)
{
	level *l = &d->sectors[x][y];
	for (int i = 0; i < MAX_ENEMIES; ++i) {
		AI_HANDLERS[l->enemies[i].at](d, x, y, &l->enemies[i]);
	}
}

void draw_enemies(level *l, int camera_x, int camera_y) {
	for (int i = 0; i < l->enemy_index; ++i) {
		draw_entity(&l->enemies[i], camera_x, camera_y);
	}
}
