#pragma once

typedef enum mode {
	MODE_MENU,
	MODE_CREATE_CHARACTER,
	MODE_INVENTORY,
	MODE_GAME,
	MODE_INTRO,
	MODE_INTRO2,
	MODE_HOWTOPLAY,
	MODE_LOSS,
	MODE_VICTORY,
} mode;

void set_mode(mode m);
void set_current_dungeon(char *name, int player_x, int player_y);

void main_game_loop();
