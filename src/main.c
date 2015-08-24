#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "game.h"
#include "level.h"
#include "entity.h"
#include "player.h"
#include "graphics.h"
#include "menu.h"

int main(int argc, char *argv[])
{
	initialize_graphics();

	set_mode(MODE_MENU);

	int x, y;

	FILE *f = fopen("dungeons/overworld/coords.dat", "r");
	if (f == NULL) {
		x = y = 1;
	} else {
		fread(&x, sizeof(x), 1, f);
		fread(&y, sizeof(y), 1, f);
		fclose(f);
	}
	
	set_current_dungeon("overworld", x, y);

	main_game_loop();

	finalize_graphics();

	printf("Goodbye!\n");
}
