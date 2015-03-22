#pragma once

#include "color.h"

#define AI_SUBTYPES 32

struct level;

typedef enum ai_type {
	AI_NONE = 0,
	AI_RANDOM_WALK
} ai_type;

typedef struct entity {
	int x, y;
	char glyph;
	color color;
	ai_type at;
	void (*collision_handler)(struct level *l, struct entity *entity);
} entity;


void draw_entity(entity *e, int camera_x, int camera_y);
void move_entity_west(entity *e, struct level *l);
void move_entity_east(entity *e, struct level *l);
void move_entity_north(entity *e, struct level *l);
void move_entity_south(entity *e, struct level *l);
