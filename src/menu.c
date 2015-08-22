#include "menu.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "color.h"
#include "graphics.h"
#include "error.h"

colored_string MENU[24];
char *ADJECTIVES[WORDFLAVOR_MARKER][6] = {
	[NEGATIVE] = {"bad", "awful", "horrible", "terrible", "crushing", "evil"},
	[POSITIVE] = {"good", "great", "fantastic", "excellent", "wonderful", "amazing"},
	[NEUTRAL] = {"mediocre", "average", "so-so", "unnotable", "normal", "regular"},
	[EMPTY] = {"empty", "hollow", "cold", "hard", "broken", "twisted"},
	[OTAKU_TITLE_DESCRIPTIVE] = {"Flaming", "Radical", "Badass", "Grim", "Intelligent", "Euphoric"},
};

char *NAMES[NAMES_MARKER][6] = {
	[OTAKU] = {"Davido", "Ken", "Franku", "Chris", "Devin", "Takashi"},
	[CHAD_FIRST_NAME] = {"Chad", "Todd", "Trevor", "Jared", "Chase", "Jason"},
	[STACY_FIRST_NAME] = {"Stacy", "Amber", "Sydney", "Tiffani", "Ashley", "Missi"},
	[NORMIE_LAST_NAME] = {"Johnson", "Smith", "Jones", "Brown", "Thomas", "Hill"},
	[OTAKU_TITLE_NAME] = {"God", "Blademaster", "Slayer", "Samurai", "Darkness", "Master"},
	[NORMIE_JOB] = {"Store Clerk", "Heavy Drinker", "Theist", "Normie", "Pothead", "Casual"},
};

char *SUFFIXES[SUFFIXES_MARKER][6] = {
	[JAPANESE] = {"kun", "san", "sama", "senpai", "sempai", "chan"},
};

void initialize_menu()
{
	memset(MENU, 0, sizeof(MENU));
	srand(time(NULL));
}

char *generate_adjective(adjectives f)
{
	return ADJECTIVES[f][rand() % 6];
}

char *generate_name(names f)
{
	return NAMES[f][rand() % 6];
}

char *generate_suffix(suffixes f)
{
	return SUFFIXES[f][rand() % 6];
}

void generate_otaku_name(char *buffer, int bufsize)
{
	snprintf(buffer, bufsize, "%s-%s, The %s %s", generate_name(OTAKU), generate_suffix(JAPANESE), generate_adjective(OTAKU_TITLE_DESCRIPTIVE), generate_name(OTAKU_TITLE_NAME));
}

void generate_chad_name(char *buffer, int bufsize)
{
	snprintf(buffer, bufsize, "%s %s, %s", generate_name(CHAD_FIRST_NAME), generate_name(NORMIE_LAST_NAME), generate_name(NORMIE_JOB));
}

void generate_stacy_name(char *buffer, int bufsize)
{
	snprintf(buffer, bufsize, "%s %s, %s", generate_name(STACY_FIRST_NAME), generate_name(NORMIE_LAST_NAME), generate_name(NORMIE_JOB));
}

void menu_line(int row, char *t, color c)
{
	strncpy(MENU[row].string, t, sizeof(MENU[row].string));
	MENU[row].c = c;
}

void draw_menu()
{
	for (int row = 0; row < 24; ++row) {
		draw_colored_string(MENU[row], 1, row + 1);
	}
}
