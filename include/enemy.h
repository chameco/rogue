#pragma once

#include "entity.h"
#include "dungeon.h"

bool collide_enemies(level *l, entity *e, int x, int y);
void update_enemies(dungeon *d);
void draw_enemies(level *l, int camera_x, int camera_y);
