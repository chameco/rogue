#include "game.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include <cuttle/debug.h>

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
bool GAME_RUNNING = 1;

void set_mode(mode m)
{
	CURRENT_MODE = m;
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
	bool level_changed;
	char inventory_line[512];
	char sprintf_buffer[256];
	DIR *d;
	FILE *f;
	struct dirent *dir;
	while (GAME_RUNNING) {
		entity *player = get_player();
		clear();
		switch (CURRENT_MODE) {
			case MODE_MENU:
				initialize_menu();
				menu_line(0, "            __           _ _             _           _ ", WHITE);
				menu_line(1, "           / _|         | | |           (_)         | |", WHITE);
				menu_line(2, "  ___  ___| |_ _   _  __| | | ___   __ _ _  __ _  __| |", WHITE);
				menu_line(3, " / __|/ _ \\  _| | | |/ _` | |/ _ \\ / _` | |/ _` |/ _` |", WHITE);
				menu_line(4, " \\__ \\  __/ | | |_| | (_| | | (_) | (_| | | (_| | (_| |", WHITE);
				menu_line(5, " |___/\\___|_|  \\__, |\\__,_|_|\\___/ \\__, |_|\\__,_|\\__,_|", WHITE);
				menu_line(6, "                __/ |               __/ |              ", WHITE);
				menu_line(7, "               |___/               |___/               ", WHITE);

				menu_line(9, "1 - Continue", WHITE);
				menu_line(10, "2 - New Game", WHITE);
				menu_line(11, "q - Quit", WHITE);

				draw_menu();
				input = getch();
				switch (input) {
					case '1':
						load_player();
						if (player->stats[HP] > 0) {
							set_mode(MODE_GAME);
						} else {
							clear();
							refresh();
							initialize_menu();

							menu_line(0, "No saved game!", WHITE);
							draw_menu();
							getch();
						}
						break;
					case '2':
						set_mode(MODE_CREATE_CHARACTER);
						break;
					case 'q':
						GAME_RUNNING = 0;
						break;
				}
				break;
			case MODE_CREATE_CHARACTER:
				d = opendir("dungeons/overworld/");
				if (d) {
					while ((dir = readdir(d)) != NULL) {
						snprintf(sprintf_buffer, 256, "dungeons/overworld/%s", dir->d_name);
						remove(sprintf_buffer);
					}
					closedir(d);
				}
				load_dungeon(&CURRENT_DUNGEON, "overworld", 1, 1);
				initialize_player();
				initialize_menu();
				menu_line(0, "Enter your name:", WHITE);
				draw_menu();
				curs_set(1);
				echo();
				move(2, 1);
				getnstr(sprintf_buffer, 32);
				curs_set(0);
				noecho();
				generate_player_name(player->name, 64, sprintf_buffer);
				set_mode(MODE_INTRO);
				break;
			case MODE_INVENTORY:
				initialize_menu();
				menu_line(0, "Inventory", BLUE);
				for (tx = 0; tx < 13; tx += 2) {
					memset(inventory_line, 0, 512);
					if (player->inventory[tx].type == EMPTY_SLOT) {
						sprintf(sprintf_buffer, "%c - Empty", 'a' + tx);
					} else {
						sprintf(sprintf_buffer, "%c - %s", 'a' + tx, player->inventory[tx].name);
					}
					strncat(inventory_line, sprintf_buffer, 512);
					strncat(inventory_line, "   ", 512);
					if (player->inventory[tx + 1].type == EMPTY_SLOT) {
						sprintf(sprintf_buffer, "%c - Empty", 'a' + tx + 1);
					} else {
						sprintf(sprintf_buffer, "%c - %s", 'a' + tx + 1, player->inventory[tx + 1].name);
					}
					strncat(inventory_line, sprintf_buffer, 512);
					menu_line(tx/2 + 1, inventory_line, WHITE);
				}
				menu_line(8, "--- PRESS ANY KEY TO CONTINUE ---", YELLOW);
				draw_menu();
				getch();
				set_mode(MODE_GAME);
				break;
			case MODE_GAME:
				if (player->stats[DEX] > 100) {
					set_mode(MODE_LOSS);
				}
				player_hud(&CURRENT_DUNGEON);
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
					case 'i':
						set_mode(MODE_INVENTORY);
						break;
					case 'u':
						message_line("Use which item?", WHITE);

						clear();
						refresh();
						draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
						draw_entity(player, player->x, player->y);
						draw_hud();
						draw_messages();

						input = getch();
						if (input <= 'z' && input >= 'a') {
							use_item(&player->inventory[input - 'a'], get_player());
						} else {
							message_line("Invalid slot.", RED);
						}
						break;
					case 'w':
						message_line("Wield which weapon?", WHITE);

						clear();
						refresh();
						draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
						draw_entity(player, player->x, player->y);
						draw_hud();
						draw_messages();

						input = getch();
						if (input <= 'z' && input >= 'a') {
							if (player->inventory[input - 'a'].type != EMPTY_SLOT) {
								player->weapon_slot = input - 'a';
							} else {
								message_line("Empty slot.", RED);
							}
						} else {
							message_line("Invalid slot.", RED);
						}
						break;
					case 'W':
						message_line("Wear which armor?", WHITE);

						clear();
						refresh();
						draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
						draw_entity(player, player->x, player->y);
						draw_hud();
						draw_messages();

						input = getch();
						if (input <= 'z' && input >= 'a') {
							if (player->inventory[input - 'a'].type != EMPTY_SLOT) {
								if (player->inventory[input - 'a'].def != -1) {
									player->armor_slot = input - 'a';
								} else {
									message_line("You can't wear that!", RED);
								}
							} else {
								message_line("Empty slot.", RED);
							}
						} else {
							message_line("Invalid slot.", RED);
						}
						break;
					case 'd':
						message_line("Describe which item?", WHITE);

						clear();
						refresh();
						draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
						draw_entity(player, player->x, player->y);
						draw_hud();
						draw_messages();

						input = getch();
						if (input <= 'z' && input >= 'a') {
							if (player->inventory[input - 'a'].type != EMPTY_SLOT) {
								message_line(player->inventory[input - 'a'].description, WHITE);
							} else {
								message_line("Empty slot.", RED);
							}
						} else {
							message_line("Invalid slot.", RED);
						}
						break;
					case ',':
						if (CURRENT_DUNGEON.sectors[1][1].items[player->x][player->y].type != EMPTY_SLOT) {
							message_line("Place in which slot?", WHITE);

							clear();
							refresh();
							draw_dungeon(&CURRENT_DUNGEON, player->x, player->y);
							draw_entity(player, player->x, player->y);
							draw_hud();
							draw_messages();

							input = getch();
							if (input <= 'z' && input >= 'a') {
								if (player->inventory[input - 'a'].type == EMPTY_SLOT) {
									memcpy(&player->inventory[input - 'a'], &CURRENT_DUNGEON.sectors[1][1].items[player->x][player->y], sizeof(item));
									memset(&CURRENT_DUNGEON.sectors[1][1].items[player->x][player->y], 0, sizeof(item));
								} else {
									message_line("Slot is not empty.", RED);
								}
							} else {
								message_line("Invalid slot.", RED);
							}
						}
						break;
					case 'q':
						save_player();
						f = fopen("dungeons/overworld/coords.dat", "w+");
						fwrite(&CURRENT_DUNGEON.player_x, sizeof(CURRENT_DUNGEON.player_x), 1, f);
						fwrite(&CURRENT_DUNGEON.player_y, sizeof(CURRENT_DUNGEON.player_y), 1, f);
						fclose(f);
						save_dungeon(&CURRENT_DUNGEON);
						GAME_RUNNING = 0;
						break;
				}
				if (level_changed) {
					move_player_dungeon(&CURRENT_DUNGEON, CURRENT_DUNGEON.player_x + tx, CURRENT_DUNGEON.player_y + ty);
				}
				update_enemies(&CURRENT_DUNGEON);
				break;
			case MODE_INTRO:
				initialize_menu();
				menu_line(0, "You are a monster.", RED);
				menu_line(2, "A vast beast, prone to anger and violence.", WHITE);
				menu_line(4, "Avaricious and cruel, like a dragon of yore.", WHITE);
				menu_line(6, "Today, you have set your sights on a prize.", WHITE);
				menu_line(7, "A prize only the worthiest can obtain...", WHITE);
				menu_line(8, "--- PRESS ANY KEY TO CONTINUE ---", YELLOW);
				draw_menu();
				getch();
				set_mode(MODE_INTRO2);
				break;
			case MODE_INTRO2:
				initialize_menu();
				menu_line(0, "A new figurine of your waifu.", YELLOW);
				menu_line(1, "You have spent years waiting.", WHITE);
				menu_line(2, "You have devoted yourself entirely.", WHITE);
				menu_line(3, "Your waifu folder contains many thousands of images.", WHITE);
				menu_line(4, "You must take this prize.", WHITE);
				menu_line(5, "It is your life's goal, and the apex of all you have worked for.", WHITE);
				menu_line(6, "--- PRESS ANY KEY TO CONTINUE ---", YELLOW);
				draw_menu();
				getch();
				set_mode(MODE_HOWTOPLAY);
				break;
			case MODE_HOWTOPLAY:
				initialize_menu();
				menu_line(0, "=== HOW TO PLAY ===", GREEN);
				menu_line(2, "Use h, j, k, and l to move.", WHITE);
				menu_line(3, "Use i to check your inventory.", WHITE);
				menu_line(4, "Use comma to pick up items, d to describe items, u to use them,", WHITE);
				menu_line(5, "w to wield weapons, and W to wear armor.", WHITE);
				menu_line(6, "Weapons will increase your ability to disgust others, and armor will dissuade the police.", WHITE);
				menu_line(7, "Your goal is to reach the convention plaza at coordinates 10,10,", WHITE);
				menu_line(8, "retrieve your figurine, and activate it to channel it's power.", WHITE);
				menu_line(10, "Normies will attempt to make conversation with you. Ignore them. They merely distract you.", WHITE);
				menu_line(11, "If you must, simply plow through them, hoping to disgust them until they flee.", WHITE);
				menu_line(12, "But beware! Cause enough of a stir, and the police will arrive, ruining any chance of success.", WHITE);
				menu_line(13, "--- PRESS ANY KEY TO CONTINUE ---", YELLOW);
				draw_menu();
				getch();
				set_mode(MODE_GAME);
				break;
			case MODE_LOSS:
				initialize_menu();
				menu_line(0, "=== FAILURE ===", RED);
				menu_line(1, "Before you can react, a police officer darts out from behind a building.", WHITE);
				menu_line(2, "He grabs your arm, and pulls you into his vehicle despite your tantrums.", WHITE);
				menu_line(3, "On account of your indecent behavior, you are sentenced to 3 months of community service.", WHITE);
				menu_line(4, "You learn many things about humanity, life, and the nature of happiness.", WHITE);
				draw_menu();
				getch();
				d = opendir("dungeons/overworld/");
				if (d) {
					while ((dir = readdir(d)) != NULL) {
						snprintf(sprintf_buffer, 256, "dungeons/overworld/%s", dir->d_name);
						remove(sprintf_buffer);
					}
					closedir(d);
				}
				GAME_RUNNING = 0;
				break;
			case MODE_VICTORY:
				initialize_menu();
				menu_line(0, "=== CONGRATULATIONS ===", YELLOW);
				menu_line(1, "You heft the object of your quest high, weighing it, feeling it, touching it.", WHITE);
				menu_line(2, "You feel validated as a human being, and return home.", WHITE);
				menu_line(3, "Your mother makes you a quality meal of chicken tenders and hot pockets, and you eat like a king.", WHITE);
				menu_line(4, "While browsing the web that night, you find the date for the next convention.", WHITE);
				menu_line(5, "As you whine for another plate of chicken tenders and readjust your cargo shorts,", WHITE);
				menu_line(6, "you fearfully mark the next time you must go outside on the calendar.", WHITE);
				draw_menu();
				getch();
				d = opendir("dungeons/overworld/");
				if (d) {
					while ((dir = readdir(d)) != NULL) {
						snprintf(sprintf_buffer, 256, "dungeons/overworld/%s", dir->d_name);
						remove(sprintf_buffer);
					}
					closedir(d);
				}
				GAME_RUNNING = 0;
				break;
				break;
		}
		clear();
		refresh();
	}
}
