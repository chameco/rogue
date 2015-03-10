#pragma once

#include <stddef.h>
#include <stdbool.h>

#include <ncurses.h>

#include "color.h"

#define LEVEL_DIM 32

struct level;
struct entity;

typedef enum tile_index {
	VOID = 0,
	GROUND,
	TREE,
	STONE_FLOOR,
	STONE_WALL,
	DOOR
} tile_index;

typedef struct tile {
	char glyph;
	color color;
	bool breakable;
	bool transparent;
	void (*collision_handler)(struct level *l, int x, int y, struct entity *entity);
} tile;

typedef struct level {
	tile_index walls[LEVEL_DIM][LEVEL_DIM];
	tile_index floor[LEVEL_DIM][LEVEL_DIM];
	int sector_index;
} level;

void load_level(level *l, char *p);
void save_level(level *l, char *p);

tile *get_wall_tile(level *l, int x, int y);
tile *get_floor_tile(level *l, int x, int y);

void draw_level(level *l, int camera_x, int camera_y);
