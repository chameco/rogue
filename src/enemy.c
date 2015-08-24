#include "enemy.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#ifndef WINDOWS
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include <cuttle/debug.h>

#include "entity.h"
#include "player.h"
#include "level.h"
#include "dungeon.h"
#include "graphics.h"

void __ai_none(dungeon *d, entity *e)
{
}

void __ai_random_walk(dungeon *d, entity *e)
{
	int dir = rand() % 4;
	switch (dir) {
		case 0:
			move_entity_north(e, d);
			break;
		case 1:
			move_entity_south(e, d);
			break;
		case 2:
			move_entity_west(e, d);
			break;
		case 3:
			move_entity_east(e, d);
			break;
	}
}

void __ai_chase(dungeon *d, entity *e)
{
	if (get_player()->stats[STR] > 0) {
		get_player()->stats[STR] -= 1;
	} else {
		int xdiff = get_player()->x - e->x;
		int ydiff = get_player()->y - e->y;
		if (xdiff == 0 && ydiff == 0) return;
		if (abs(ydiff) > abs(xdiff)) {
			if (ydiff > 1) {
				move_entity_south(e, d);
			} else if (ydiff < -1) {
				move_entity_north(e, d);
			}
		} else if (abs(xdiff) > abs(ydiff)) {
			if (xdiff > 1) {
				move_entity_east(e, d);
			} else if (xdiff < -1) {
				move_entity_west(e, d);
			}
		}
	}
}

void __ai_chad(dungeon *d, entity *e)
{
	__ai_chase(d, e);
	char sprintf_buffer[256];
	int hp = e->stats[HP];
	if (rand() % 2 == 0) {
		if (hp < 1) {
			snprintf(sprintf_buffer, 256, "%s sprints away, unable to contain his disgust.", e->name);
		} else if (hp < 2) {
			snprintf(sprintf_buffer, 256, "%s is disgusted", e->name);
		} else if (hp < 3) {
			snprintf(sprintf_buffer, 256, "%s shouts \"Brah, get away from me!\".", e->name);
		} else if (hp < 4) {
			snprintf(sprintf_buffer, 256, "%s is extremely uncomfortable.", e->name);
		} else if (hp < 5) {
			snprintf(sprintf_buffer, 256, "%s laughs harder than he ever has.", e->name);
		} else if (hp < 6) {
			snprintf(sprintf_buffer, 256, "%s has never seen a bigger loser.", e->name);
		} else if (hp < 7) {
			snprintf(sprintf_buffer, 256, "Sweat pours %s's face.", e->name);
		} else if (hp < 8) {
			snprintf(sprintf_buffer, 256, "%s is cringing noticeably.", e->name);
		} else if (hp < 9) {
			snprintf(sprintf_buffer, 256, "%s says \"Brah, cut that shit out.\"", e->name);
		} else if (hp < 10) {
			snprintf(sprintf_buffer, 256, "%s is unfazed.", e->name);
		}
		if (hp < 10) {
			message_line(sprintf_buffer, GREEN);
		}
	}
}

void __ai_stacy(dungeon *d, entity *e)
{
	__ai_chase(d, e);
	char sprintf_buffer[256];
	int hp = e->stats[HP];
	if (rand() % 2 == 0) {
		if (hp < 1) {
			snprintf(sprintf_buffer, 256, "%s walks away, unable to contain her disgust.", e->name);
		} else if (hp < 2) {
			snprintf(sprintf_buffer, 256, "%s is disgusted", e->name);
		} else if (hp < 3) {
			snprintf(sprintf_buffer, 256, "%s shouts \"Now this is starting to get old.\".", e->name);
		} else if (hp < 4) {
			snprintf(sprintf_buffer, 256, "%s is extremely uncomfortable.", e->name);
		} else if (hp < 5) {
			snprintf(sprintf_buffer, 256, "%s laughs harder than she ever has.", e->name);
		} else if (hp < 6) {
			snprintf(sprintf_buffer, 256, "%s has never seen a bigger loser.", e->name);
		} else if (hp < 7) {
			snprintf(sprintf_buffer, 256, "%s says \"I can't even take this dork.\".", e->name);
		} else if (hp < 8) {
			snprintf(sprintf_buffer, 256, "%s is cringing noticeably.", e->name);
		} else if (hp < 9) {
			snprintf(sprintf_buffer, 256, "%s says \"OMG, get out of my field of vision.\".", e->name);
		} else if (hp < 10) {
			snprintf(sprintf_buffer, 256, "%s is unfazed.", e->name);
		}
		if (hp < 10) {
			message_line(sprintf_buffer, GREEN);
		}
	}
}

void __ai_otaku(dungeon *d, entity *e)
{
	__ai_chase(d, e);
	char sprintf_buffer[256];
	int hp = e->stats[HP];
	if (rand() % 2 == 0) {
		if (hp < 1) {
			snprintf(sprintf_buffer, 256, "%s runs home to drown his mediocrity in mass media..", e->name);
		} else if (hp < 2) {
			snprintf(sprintf_buffer, 256, "%s is sweating.", e->name);
		} else if (hp < 3) {
			snprintf(sprintf_buffer, 256, "%s shouts \"A worthy opponent!\".", e->name);
		} else if (hp < 4) {
			snprintf(sprintf_buffer, 256, "%s is starting to get nervous", e->name);
		} else if (hp < 5) {
			snprintf(sprintf_buffer, 256, "%s screams quotes from battle shounen.", e->name);
		} else if (hp < 6) {
			snprintf(sprintf_buffer, 256, "%s gloats about his powerlevel.", e->name);
		} else if (hp < 7) {
			snprintf(sprintf_buffer, 256, "%s shouts \"You're not fit to tie my kimono!\".", e->name);
		} else if (hp < 8) {
			snprintf(sprintf_buffer, 256, "%s is laughs like only someone with no social graces can..", e->name);
		} else if (hp < 9) {
			snprintf(sprintf_buffer, 256, "%s screams \"You'll have to try harder than that!\".", e->name);
		} else if (hp < 10) {
			snprintf(sprintf_buffer, 256, "%s is unfazed.", e->name);
		}
		if (hp < 10) {
			message_line(sprintf_buffer, GREEN);
		}
	}
}

void (*AI_HANDLERS[AI_TYPE_MARKER])(dungeon *d, entity *e) = {
	[AI_NONE] = __ai_none,
	[AI_RANDOM_WALK] = __ai_random_walk,
	[AI_CHASE] = __ai_chase,
	[AI_CHAD] = __ai_chad,
	[AI_STACY] = __ai_stacy,
	[AI_OTAKU] = __ai_otaku,
};

bool collide_enemies(level *l, entity *e, int x, int y)
{
	for (int i = 0; i < l->enemy_index; ++i) {
		if (l->enemies[i].x != -1) {
			if (l->enemies[i].x == x && l->enemies[i].y == y) {
				if (e == get_player()) {
					attack_with_item(&e->inventory[e->weapon_slot], e, &l->enemies[i]);
				}
				return 1;
			}
		}
	}
	return 0;
}

void update_enemies(dungeon *d)
{
	level *l = &d->sectors[1][1];
	for (int i = 0; i < l->enemy_index; ++i) {
		if (l->enemies[i].x != -1) {
			AI_HANDLERS[l->enemies[i].at](d, &l->enemies[i]);
		}
	}
}

void draw_enemies(level *l, int camera_x, int camera_y) {
	for (int i = 0; i < l->enemy_index; ++i) {
		if (l->enemies[i].x != -1) {
			draw_entity(&l->enemies[i], camera_x, camera_y);
		}
	}
}
