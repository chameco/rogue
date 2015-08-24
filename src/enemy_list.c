#include "enemy_list.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "enemy.h"
#include "entity.h"
#include "level.h"
#include "dungeon.h"
#include "menu.h"
#include "graphics.h"

void __handler_otaku(level *l, entity *e, entity *other)
{
	message_line(e->name, GREEN);
}

void spawn_enemy(entity *e, enemy_type et, int x, int y)
{
	e->x = x;
	e->y = y;
	switch (et) {
		case ENEMY_OTAKU:
			e->glyph = '@';
			e->color = RED;
			e->at = AI_OTAKU;
			e->stats[HP] = 10;
			e->stats[STR] = 7;
			e->stats[DEF] = 7;
			e->stats[DEX] = 7;
			generate_otaku_name(e->name, 64);
			break;
		case ENEMY_CHAD:
			e->glyph = '@';
			e->color = BLUE;
			e->at = AI_CHAD;
			e->stats[HP] = 10;
			e->stats[STR] = 5;
			e->stats[DEF] = 3;
			e->stats[DEX] = 3;
			generate_chad_name(e->name, 64);
			break;
		case ENEMY_STACY:
			e->glyph = '@';
			e->color = YELLOW;
			e->at = AI_STACY;
			e->stats[HP] = 10;
			e->stats[STR] = 3;
			e->stats[DEF] = 3;
			e->stats[DEX] = 5;
			generate_stacy_name(e->name, 64);
			break;
		default:
			log_err("No entity with type %d", et);
			exit(1);
			break;
	}
}
