#include "windows.h"
#include "world.h"

COORD GetConsoleCursorPosition();
class World;

void redraw_world(World *w);

void draw(int x, int y, const char *c, World *w, int color);

void draw_world(World *w);
