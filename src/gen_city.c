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

#include "gen_jungle.h"

void __gen_city(level *l)
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
		generate_tile(l,&c, 1, TREE);
	}
	for (int i = 0; i < 5; ++i) {
		generate_room(l, &c, 2, 5, 5, STONE_WALL, STONE_FLOOR);
	}
}
