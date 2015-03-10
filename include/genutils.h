#pragma once

#include "level.h"

typedef struct claimed_tiles {
	int priority[LEVEL_DIM][LEVEL_DIM];
} claimed_tiles;

void generate_tile(level *l, claimed_tiles *c, int prio, tile_index wall);
void generate_room(level *l, claimed_tiles *c, int prio, int w, int h, tile_index wall, tile_index floor);
