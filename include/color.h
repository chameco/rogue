#pragma once

typedef struct color {
	short fg, bg;
} color;

typedef struct colored_string {
	char string[100];
	color c;
} colored_string;

color WHITE;
color RED;
color GREEN;
color BLUE;
color YELLOW;
color MAGENTA;

void initialize_color();
void draw_glyph(char g, color c, int x, int y);
void draw_colored_string(colored_string s, int x, int y);
