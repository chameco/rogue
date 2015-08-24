#pragma once

#include "color.h"

typedef enum adjectives {
	NEGATIVE=0,
	POSITIVE,
	NEUTRAL,
	EMPTY,
	OTAKU_TITLE_DESCRIPTIVE,
	NOSTALGIC,
	ADJECTIVES_MARKER,
} adjectives;

typedef enum names {
	OTAKU=0,
	CHAD_FIRST_NAME,
	STACY_FIRST_NAME,
	NORMIE_LAST_NAME,
	OTAKU_TITLE_NAME,
	NORMIE_JOB,
	NAMES_MARKER,
} names;

typedef enum suffixes {
	JAPANESE=0,
	SUFFIXES_MARKER,
} suffixes;

void initialize_menu();

char *generate_adjective(adjectives f);
char *generate_name(names f);
char *generate_suffix(suffixes f);

void generate_player_name(char *buffer, int bufsize, char *base);
void generate_otaku_name(char *buffer, int bufsize);
void generate_chad_name(char *buffer, int bufsize);
void generate_stacy_name(char *buffer, int bufsize);

void menu_line(int row, char *t, color c);
void draw_menu();
