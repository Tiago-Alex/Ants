#ifndef DRAW_H
#define DRAW_H

#include "windows.h"
#include "world.h"

class World;

class Draw {
public:
  static void draw_world(World *w);
  static void draw(int x, int y, const char *c, World *w, int color);
  static COORD GetConsoleCursorPosition();
  static void refresh_world(World *w);
};

#endif
