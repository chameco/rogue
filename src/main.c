#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include <ncurses.h>

#include "game.h"
#include "level.h"
#include "entity.h"
#include "player.h"
#include "graphics.h"
#include "menu.h"

int main(int argc, char *argv[])
{
	initialize_graphics();

	initialize_player();
	initialize_menu();

	menu_line(0, "roguelike", BLUE);
	char sprintf_buffer[256];
	sprintf(sprintf_buffer, "~ memories of a %s world", generate_adjective(EMPTY));
	menu_line(1, sprintf_buffer, WHITE);
	set_mode(MODE_MENU);
	
	set_current_dungeon("overworld", 1, 1);

	main_game_loop();

	finalize_graphics();

	printf("Goodbye!\n");
}
