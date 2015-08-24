#include "item.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include "curses.h"
#endif

#include <cuttle/debug.h>

#include "error.h"
#include "entity.h"
#include "color.h"
#include "graphics.h"
#include "game.h"

void make_item(item *i, item_type type)
{
	i->type = type;
	switch(type) {
		case OTAKU_MACGUFFIN:
			strncpy(i->name, "Holy Macguffin", 64);
			strncpy(i->description, "wooooo", 256);
			i->glyph = '*';
			i->dmg = -1;
			i->def = -1;
			i->ev = -1;
			break;

		case WINDENBO_BS:
			strncpy(i->name, "Windenbo BS Handheld Console", 64);
			strncpy(i->description, "A handheld gaming console by Windenbo Corporation.", 256);
			i->glyph = ')';
			i->dmg = 5;
			i->def = -1;
			i->ev = 4;
			break;
		case FOAM_KATANA:
			strncpy(i->name, "Foam Katana", 64);
			strncpy(i->description, "A sword made of superior Japanese styrofoam, folded 1,000 times.", 256);
			i->glyph = ')';
			i->dmg = 7;
			i->def = -1;
			i->ev = 2;
			break;
		case DAKIMAKURA:
			strncpy(i->name, "Dakimakura (pillow included)", 64);
			strncpy(i->description, "A body pillow cover emblazoned with (insert best girl here).", 256);
			i->glyph = ')';
			i->dmg = 9;
			i->def = -1;
			i->ev = 0;
			break;
		case CELLPHONE_STRAP:
			strncpy(i->name, "Cellphone Strap", 64);
			strncpy(i->description, "A phone charm in the form of one of your favorite characters.", 256);
			i->glyph = ')';
			i->dmg = 3;
			i->def = -1;
			i->ev = 6;
			break;
		
		case SHOUNEN_SHIRT:
			strncpy(i->name, "Shounen Shirt", 64);
			strncpy(i->description, "A shirt depicting a fight between colorful characters.", 256);
			i->glyph = '[';
			i->dmg = 1;
			i->def = 5;
			i->ev = 1;
			break;
		case SEINEN_SHIRT:
			strncpy(i->name, "Seinen Shirt", 64);
			strncpy(i->description, "A shirt depicting some really edgy stuff. Offputting.", 256);
			i->glyph = '[';
			i->dmg = 1;
			i->def = 4;
			i->ev = 1;
			break;
		case SHOUJO_SHIRT:
			strncpy(i->name, "Shoujo Shirt", 64);
			strncpy(i->description, "A shirt depicting some young girls in strange costumes. People always give you strange looks when you wear it.", 256);
			i->glyph = '[';
			i->dmg = 1;
			i->def = 3;
			i->ev = 5;
			break;
		case OBSCENE_SHIRT:
			strncpy(i->name, "Obscene Shirt", 64);
			strncpy(i->description, "No. Just stop.", 256);
			i->glyph = '[';
			i->dmg = 1;
			i->def = 1;
			i->ev = 5;
			break;
		case LACK_OF_SHIRT:
			strncpy(i->name, "Lack of a Shirt", 64);
			strncpy(i->description, "Exactly what is says on the tin. Or the lack thereof.", 256);
			i->glyph = '[';
			i->dmg = 1;
			i->def = 0;
			i->ev = 9;
			break;

		case DEODORANT:
			strncpy(i->name, "Deodorant", 64);
			strncpy(i->description, "Deodorant, for a fresh scent. (Reduces disturbance level.)", 256);
			i->glyph = '%';
			i->dmg = 1;
			i->def = -1;
			i->ev = 0;
			break;
		case REODORANT:
			strncpy(i->name, "Reodorant", 64);
			strncpy(i->description, "Reodorant, for a slightly less fresh scent. (Repels enemies.)", 256);
			i->glyph = '%';
			i->dmg = 1;
			i->def = -1;
			i->ev = 0;
			break;
		case SAPPY_MEAL:
			strncpy(i->name, "Sappy Meal", 64);
			strncpy(i->description, "A delicious and nutricious Sappy Meal, complete with a low-quality figurine. Pfft, casuals.", 256);
			i->glyph = '%';
			i->dmg = 1;
			i->def = -1;
			i->ev = 0;
			break;
		default:
			message_line("No such item.", RED);
			break;
	}
}

void attack_with_item(item *i, entity *wielder, entity *target)
{
	switch(i->type) {
		case OTAKU_MACGUFFIN:
		case DEODORANT:
		case REODORANT:
		case SAPPY_MEAL:
			message_line("You can't attack with that!", RED);
			return;
		case WINDENBO_BS:
			message_line("You play a Japanse idol game on your console. Loudly.", BLUE);
			break;
		case FOAM_KATANA:
			message_line("You perform some sick katana tricks, demonstrating your mastery of the blade.", BLUE);
			break;
		case DAKIMAKURA:
			message_line("You stroke your pillow furiously.", BLUE);
			break;
		case CELLPHONE_STRAP:
			message_line("You swing the phone charm while singing a theme song. You're the cutest middle-aged balding fat man you know!", BLUE);
			break;
		case SHOUNEN_SHIRT:
		case SEINEN_SHIRT:
		case SHOUJO_SHIRT:
		case OBSCENE_SHIRT:
			message_line("You swing the shirt in the air, but are too afraid to smack anyone with it. It's awkward all the same.", BLUE);
			break;
		default:
			message_line("No such item.", RED);
			return;
	};
	target->stats[HP] -= i->dmg;
	if (target->stats[HP] < 0) {
		target->x = -1;
		if (wielder->inventory[wielder->armor_slot].def > 0) {
			if (rand() % wielder->inventory[wielder->armor_slot].def) {
				wielder->stats[DEX] += 1;
			}
		} else {
			wielder->stats[DEX] += 1;
		}
	}
}

void use_item(item *i, entity *user)
{
	switch(i->type) {
		case OTAKU_MACGUFFIN:
			set_mode(MODE_VICTORY);
			break;
		case DEODORANT:
			user->stats[DEX] -= 10;
			i->type = EMPTY_SLOT;
			break;
		case REODORANT:
			user->stats[STR] += 500;
			i->type = EMPTY_SLOT;
			break;
		case SAPPY_MEAL:
			message_line("Mmm! Tendies!", YELLOW);
			i->type = EMPTY_SLOT;
			break;
		default:
			message_line("You can't use that!", RED);
			break;
	};
}
