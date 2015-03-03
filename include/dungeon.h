#pragma once

#include "level.h"

typedef struct dungeon {
	char name[64];
	level sectors[3][3]; // keep 9 sectors in memory, current and all adjacent
	int player_x;
	int player_y;
} dungeon;

int universal_to_sector(int u);
int sector_to_universal(int s, int sector_index);
void load_dungeon(dungeon *d, char *name, int player_x, int player_y);
void save_dungeon(dungeon *d);
void move_player_dungeon(dungeon *d, int player_x, int player_y);
void draw_dungeon(dungeon *d, int camera_x, int camera_y);
