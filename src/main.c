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

	hud_line(0, "testing hud", GREEN);
	menu_line(0, "QUEST FOR THE CITY OF GOLD", YELLOW);
	set_mode(MODE_MENU);
	
	set_current_dungeon("overworld", 1, 1);

	main_game_loop();

	finalize_graphics();

	printf("Goodbye!\n");
}
