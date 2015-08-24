#pragma once

#include "color.h"

#define MAPVIEW_RADIUS_X 15
#define MAPVIEW_RADIUS_Y 9

void initialize_graphics();
void finalize_graphics();

void hud_line(int row, char *t, color c);
void draw_hud();

void message_line(char *t, color c);
void draw_messages();
