#pragma once

#include "color.h"
#include "level.h"

typedef struct entity {
	int x, y;
	char glyph;
	color color;
} entity;

void draw_entity(entity *e, int camera_x, int camera_y);
void move_entity_west(entity *e, level *l);
void move_entity_east(entity *e, level *l);
void move_entity_north(entity *e, level *l);
void move_entity_south(entity *e, level *l);
