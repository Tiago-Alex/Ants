#include "world.h"
#include "windows.h"

COORD GetConsoleCursorPosition();
class World;

void draw(int x, int y, const char *c, World *w);

void draw_world(World *w);
