#pragma once

typedef enum mode {
	MODE_MENU,
	MODE_GAME
} mode;

void set_mode(mode m);
void set_current_dungeon(char *name, int player_x, int player_y);

void main_game_loop();
