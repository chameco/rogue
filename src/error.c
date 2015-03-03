#include "error.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ncurses.h>

#include <cuttle/debug.h>

void raise_error(char *msg) {
	fputs(msg, stderr);
	endwin();
	exit(1);
}
