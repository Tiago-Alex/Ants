#ifndef DRAW_H
#define DRAW_H

#include "windows.h"
#include "world.h"

COORD GetConsoleCursorPosition();
class World;

void refresh_world(World *w);

void draw(int x, int y, const char *c, World *w, int color);

void draw_world(World *w);

#endif
