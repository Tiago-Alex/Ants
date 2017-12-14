#ifndef WORLD_H
#define WORLD_H

#include "nest.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Nest;

class World {
  int width, height;

  vector<Nest *> nests;

public:
  World(int x, int y);
  void set_world_size(int x, int y);

  int get_world_width() { return width; }

  int get_world_height() { return height; }

  vector<Nest *> get_nests() { return nests; }

  void add_nest(Nest *n);

  Nest *get_nest_from_id(int id);

  const string get_elements();
};

#endif
