#include "gen_city.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "level.h"
#include "genutils.h"
#include "graphics.h"
#include "enemy_list.h"

void __gen_city(level *l, int prio)
{
	memset(l, 0, sizeof(level));
	claimed_tiles c;
	memset(&c, 0, sizeof(c));
	for (int x = 0; x < LEVEL_DIM; ++x) {
		for (int y = 0; y < LEVEL_DIM; ++y) {
			l->floor[x][y] = GROUND;
		}
	}
	for (int i = 0; i < LEVEL_DIM; ++i) {
		generate_tile(l, &c, prio, TREE);
	}
	for (int i = 0; i < 2; ++i) {
		generate_room(l, &c, prio + 1, 10, 10, STONE_WALL, STONE_FLOOR);
	}
	spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_OTAKU, 1, 1);
	spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_CHAD, 1, 2);
	spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_STACY, 2, 1);
}
