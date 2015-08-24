#include "dispatch_gen.h"

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
#include "level.h"
#include "gen_city.h"

void dispatch_gen(level *l, int x, int y)
{
	if (x <= 10 && y <= 10 && !(x == 10 && y == 10)) __gen_city(l, 1);
	if (x == 10 && y == 10) __gen_finalboss(l, 1);
	claimed_tiles c;
	memset(&c, 0, sizeof(c));
	int prio = 1;
	if (x == 0) {
		generate_west_wall(l, &c, prio++, STONE_WALL);
	} else if (x == 10) {
		generate_east_wall(l, &c, prio++, STONE_WALL);
	}
	if (y == 0) {
		generate_north_wall(l, &c, prio++, STONE_WALL);
	} else if (y == 10) {
		generate_south_wall(l, &c, prio++, STONE_WALL);
	}
}
