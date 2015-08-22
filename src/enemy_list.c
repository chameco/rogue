#include "enemy_list.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include <ncurses.h>

#include <cuttle/debug.h>

#include "enemy.h"
#include "entity.h"
#include "level.h"
#include "dungeon.h"
#include "menu.h"
#include "graphics.h"

void __handler_otaku(level *l, entity *e, entity *other)
{
	hud_line(2, e->name, GREEN);
}

void spawn_enemy(entity *e, enemy_type et, int x, int y)
{
	e->x = x;
	e->y = y;
	switch (et) {
		case ENEMY_OTAKU:
			e->glyph = '@';
			e->color = RED;
			e->at = AI_NONE;
			generate_otaku_name(e->name, 64);
			e->collision_handler = __handler_otaku;
			break;
		case ENEMY_CHAD:
			e->glyph = '@';
			e->color = BLUE;
			e->at = AI_NONE;
			generate_chad_name(e->name, 64);
			e->collision_handler = __handler_otaku;
			break;
		case ENEMY_STACY:
			e->glyph = '@';
			e->color = MAGENTA;
			e->at = AI_NONE;
			generate_stacy_name(e->name, 64);
			e->collision_handler = __handler_otaku;
			break;
		default:
			log_err("No entity with type %d", et);
	}
}
