#include "game.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <ncurses.h>

#include "level.h"
#include "dungeon.h"
#include "entity.h"
#include "enemy.h"
#include "player.h"
#include "graphics.h"
#include "menu.h"
#include "error.h"

#include "gen_city.h"

mode CURRENT_MODE;
dungeon CURRENT_DUNGEON;
bool GAME_RUNNING = true;

void set_mode(mode m)
{
	CURRENT_MODE= m;
}

void set_current_dungeon(char *name, int player_x, int player_y)
{
	//generate_overworld();
	load_dungeon(&CURRENT_DUNGEON, name, player_x, player_y);
}

void main_game_loop()
{
	int input;
	int tx, ty; // temporaries
	int count = 0;
	bool level_changed;
	while (GAME_RUNNING) {
		entity *player = get_player();
		clear();
		switch (CURRENT_MODE) {
			case MODE_MENU:
				draw_menu();
				input = getch();
				switch (input) {
					case ' ':
					case '\n':
						set_mode(MODE_GAME);
						break;
				}
				break;
			case MODE_GAME:

				count = 0;
				for (tx = 0; tx < LEVEL_DIM; ++tx) {
					for (ty = 0; ty < LEVEL_DIM; ++ty) {
						if (CURRENT_DUNGEON.sectors[1][1].walls[tx][ty] != VOID) {
							++count;
						}
					}
				}
				draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
				draw_entity(player, player->x, player->y);
				draw_hud();
				draw_messages();

				input = getch();
				tx = ty = 0;
				switch (input) {
					case 'h':
						level_changed = move_entity_west(player, &CURRENT_DUNGEON);
						tx = -1;
						break;
					case 'l':
						level_changed = move_entity_east(player, &CURRENT_DUNGEON);
						tx = 1;
						break;
					case 'k':
						level_changed = move_entity_north(player, &CURRENT_DUNGEON);
						ty = -1;
						break;
					case 'j':
						level_changed = move_entity_south(player, &CURRENT_DUNGEON);
						ty = 1;
						break;
					case 'q':
						GAME_RUNNING = false;
						break;
				}
				if (level_changed) {
					move_player_dungeon(&CURRENT_DUNGEON, CURRENT_DUNGEON.player_x + tx, CURRENT_DUNGEON.player_y + ty);
				}
				break;
		}
		refresh();
	}
}
