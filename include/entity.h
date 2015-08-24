#pragma once

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include "item.h"
#include "color.h"

struct level;
struct dungeon;

typedef enum ai_type {
	AI_NONE=0,
	AI_RANDOM_WALK,
	AI_CHASE,
	AI_CHAD,
	AI_STACY,
	AI_OTAKU,
	AI_TYPE_MARKER,
} ai_type;

typedef enum entity_stats {
	HP=0,
	STR,
	DEF,
	DEX,
	ENTITY_STATS_MARKER
} entity_stats;

typedef struct entity {
	int x, y;
	char glyph;
	color color;
	ai_type at;
	char name[64];
	int stats[ENTITY_STATS_MARKER];
	int weapon_slot;
	int armor_slot;
	item inventory[26];
} entity;


void draw_entity(entity *e, int camera_x, int camera_y);
bool move_entity_worker(entity *e, struct dungeon *l, int tx, int ty);
bool move_entity_west(entity *e, struct dungeon *l);
bool move_entity_east(entity *e, struct dungeon *l);
bool move_entity_north(entity *e, struct dungeon *l);
bool move_entity_south(entity *e, struct dungeon *l);
