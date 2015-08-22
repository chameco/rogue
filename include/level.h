#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <ncurses.h>

#include "color.h"
#include "entity.h"

#define LEVEL_DIM 32
#define MAX_ENEMIES 64

struct level;

typedef enum tile_index {
	VOID = 0,
	GROUND,
	TREE,
	STONE_FLOOR,
	STONE_WALL,
	DOOR,
	TILE_INDEX_MARKER,
} tile_index;

typedef struct tile {
	char glyph;
	color color;
	bool breakable;
	bool transparent;
	void (*collision_handler)(struct level *l, int x, int y, entity *entity);
} tile;

typedef struct level {
	tile_index walls[LEVEL_DIM][LEVEL_DIM];
	tile_index floor[LEVEL_DIM][LEVEL_DIM];
	entity enemies[MAX_ENEMIES];
	int enemy_index;
} level;

void load_level(level *l, char *dungeon, int x, int y);
void save_level(level *l, char *dungeon, int x, int y);

tile *get_wall_tile(level *l, int x, int y);
tile *get_floor_tile(level *l, int x, int y);

void draw_level(level *l, int camera_x, int camera_y);
