#pragma once

struct entity;

typedef enum item_type {
	EMPTY_SLOT=0,

	//goal
	OTAKU_MACGUFFIN,

	//weapons
	WINDENBO_BS,
	FOAM_KATANA,
	DAKIMAKURA,
	CELLPHONE_STRAP,

	//armor
	SHOUNEN_SHIRT,
	SEINEN_SHIRT,
	SHOUJO_SHIRT,
	OBSCENE_SHIRT,
	LACK_OF_SHIRT,

	//potions
	DEODORANT,
	REODORANT,
	SAPPY_MEAL,

	ITEM_ID_MARKER,
} item_type;

typedef struct item {
	item_type type;
	char name[64];
	char description[256];
	char glyph;
	int dmg;
	int def;
	int ev;
} item;

void make_item(item *i, item_type type);
void attack_with_item(item *i, struct entity *wielder, struct entity *target);
void use_item(item *i, struct entity *user);
