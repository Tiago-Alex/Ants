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
  World(int, int);
  void set_window_size(int, int);

  int get_perc_tocreate_new_ant(int n);

  int get_perc_transfered_to_ant(int n);

  int window_width() { return width; }

  int window_height() { return height; }

  vector<Nest *> get_nests() { return nests; }

  void add_nest(Nest *n);

  Nest *get_nest_from_id(int id);
};

#endif
