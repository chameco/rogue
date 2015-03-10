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
#include "player.h"
#include "graphics.h"
#include "menu.h"
#include "error.h"

#include "gen_jungle.h"
#include "gen_city.h"

mode CURRENT_MODE;
//level CURRENT_LEVEL;
dungeon CURRENT_DUNGEON;
bool GAME_RUNNING = true;

void set_mode(mode m)
{
	CURRENT_MODE= m;
}

void generate_overworld() //TODO: temp
{
	dungeon d;
	strcpy(d.name, "overworld");
	d.player_x = 1;
	d.player_y = 1;
	/*for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			__gen_jungle(&d.sectors[i][j]);
		}
	}
	save_dungeon(&d);*/
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
	char s[100];
	int count = 0;
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
				sprintf(s, "trees: %d", count);
				hud_line(1, s, RED);
				sprintf(s, "x, y: %d, %d", CURRENT_DUNGEON.player_x, CURRENT_DUNGEON.player_y);
				hud_line(2, s, RED);
				//draw_level(&CURRENT_LEVEL, player->x, player->y);
				draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
				draw_entity(player, player->x, player->y);
				draw_hud();
				draw_messages();

				input = getch();
				switch (input) {
					case 'h':
						move_entity_west(player, &CURRENT_DUNGEON.sectors[1][1]);
						break;
					case 'l':
						move_entity_east(player, &CURRENT_DUNGEON.sectors[1][1]);
						break;
					case 'k':
						move_entity_north(player, &CURRENT_DUNGEON.sectors[1][1]);
						break;
					case 'j':
						move_entity_south(player, &CURRENT_DUNGEON.sectors[1][1]);
						break;
					case 'q':
						GAME_RUNNING = false;
						break;
				}
				tx = 0;
				ty = 0;
				if (player->x < 0) {
					tx = -1;
				} else if (player->x >= LEVEL_DIM) {
					tx = 1;
				}
				if (player->y < 0) {
					ty = -1;
				} else if (player->y >= LEVEL_DIM) {
					ty = 1;
				}
				if (tx != 0 || ty != 0) {
					if (CURRENT_DUNGEON.player_x == 0 && tx == -1) {
						player->x = 0;
						break;
					} else {
						player->x = universal_to_sector(sector_to_universal(player->x, CURRENT_DUNGEON.player_x));
					}
					if (CURRENT_DUNGEON.player_y == 0 && ty == -1) {
						player->y = 0;
						break;
					} else {
						player->y = universal_to_sector(sector_to_universal(player->y, CURRENT_DUNGEON.player_y));
					}
					move_player_dungeon(&CURRENT_DUNGEON, CURRENT_DUNGEON.player_x + tx, CURRENT_DUNGEON.player_y + ty);
				}
				break;
		}
		refresh();
	}
}
