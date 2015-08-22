#pragma once

#include "dungeon.h"
#include "entity.h"

typedef enum enemy_type {
	ENEMY_OTAKU=0,
	ENEMY_CHAD,
	ENEMY_STACY,
} enemy_type;

void spawn_enemy(entity *e, enemy_type et, int x, int y);
