#include "enemy.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

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
			move_entity_north(e, &d->sectors[x][y]);
			break;
		case 1:
			move_entity_south(e, &d->sectors[x][y]);
			break;
		case 2:
			move_entity_west(e, &d->sectors[x][y]);
			break;
		case 3:
			move_entity_east(e, &d->sectors[x][y]);
			break;
	}
}

void (*AI_HANDLERS[AI_SUBTYPES])(dungeon *d, int x, int y, entity *e) = {
	__ai_none,
	__ai_random_walk,
};

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
