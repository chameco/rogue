#include "error.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

void raise_error(char *msg) {
	fputs(msg, stderr);
	endwin();
	exit(1);
}
