#include "gen_city.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "error.h"
#include "item.h"
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
	generate_room(l, &c, prio + 1, 4, 0, 28, 28, STONE_WALL, STONE_FLOOR);
	for (int x = 0; x < LEVEL_DIM; ++x) {
		for (int y = 0; y < LEVEL_DIM; ++y) {
			if (l->floor[x][y] == GROUND && l->walls[x][y] == VOID) {
				if (rand() % 20 == 0) {
					if (l->enemy_index < 60) {
						spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_CHAD, x, y);
					}
				}
				if (rand() % 20 == 0) {
					if (l->enemy_index < 60) {
						spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_STACY, x, y);
					}
				}
				if (rand() % 40 == 0) {
					if (l->enemy_index < 60) {
						spawn_enemy(&l->enemies[l->enemy_index++], ENEMY_OTAKU, x, y);
					}
				}
			}
		}
	}

	for (int x = 0; x < LEVEL_DIM; ++x) {
		for (int y = 0; y < LEVEL_DIM; ++y) {
			if (l->floor[x][y] == GROUND && l->walls[x][y] == VOID) {
				if (rand() % 40 == 0) {
					make_item(&l->items[x][y], (rand() % (ITEM_ID_MARKER - 2)) + 2);
				}
			}
		}
	}
}

void __gen_finalboss(level *l, int prio)
{
	memset(l, 0, sizeof(level));
	claimed_tiles c;
	memset(&c, 0, sizeof(c));
	for (int x = 0; x < LEVEL_DIM; ++x) {
		for (int y = 0; y < LEVEL_DIM; ++y) {
			l->floor[x][y] = PLAZA;
		}
	}
	make_item(&l->items[LEVEL_DIM/2][LEVEL_DIM/2], OTAKU_MACGUFFIN);
}
