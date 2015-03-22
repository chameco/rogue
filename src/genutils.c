#include "genutils.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "error.h"
#include "level.h"

void generate_tile(level *l, claimed_tiles *c, int prio, tile_index wall)
{
	int x = rand() % LEVEL_DIM;
	int y = rand() % LEVEL_DIM;

	if (prio > c->priority[x][y]) {
		l->walls[x][y] = wall;
		c->priority[x][y] = prio;
	}
}

void generate_room(level *l, claimed_tiles *c, int prio, int w, int h, tile_index wall, tile_index floor)
{
	int x = rand() % (LEVEL_DIM - w);
	int y = rand() % (LEVEL_DIM - h);
	int mx = x + w;
	int my = y + h;
	for (int i = x; i < mx; ++i) {
		for (int j = y; j < my; ++j) {
			if (prio <= c->priority[i][j]) {
				return;
			}
		}
	}
	for (int i = x; i < mx; ++i) {
		for (int j = y; j < my; ++j) {
			l->floor[i][j] = floor;
			l->walls[i][j] = VOID;
			if (i == x || i == mx - 1 || j == y || j == my - 1) {
				l->walls[i][j] = wall;
				c->priority[i][j] = prio;
			}
		}
	}
}
