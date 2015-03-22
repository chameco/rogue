#pragma once

#include "entity.h"
#include "dungeon.h"

void update_enemies(dungeon *d, int x, int y);
void draw_enemies(level *l, int camera_x, int camera_y);
