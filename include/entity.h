#pragma once

#include <stdbool.h>
#include "item.h"
#include "color.h"

#define AI_SUBTYPES 32

struct level;
struct dungeon;

typedef enum ai_type {
	AI_NONE = 0,
	AI_RANDOM_WALK
} ai_type;

typedef struct entity {
	int x, y;
	char glyph;
	color color;
	ai_type at;
	item *weapon;
	item inventory[26];
	void (*collision_handler)(struct level *l, struct entity *entity);
} entity;


void draw_entity(entity *e, int camera_x, int camera_y);
bool move_entity_worker(entity *e, struct dungeon *l, int tx, int ty);
bool move_entity_west(entity *e, struct dungeon *l);
bool move_entity_east(entity *e, struct dungeon *l);
bool move_entity_north(entity *e, struct dungeon *l);
bool move_entity_south(entity *e, struct dungeon *l);
