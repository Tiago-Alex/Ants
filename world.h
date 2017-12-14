#ifndef WORLD_H
#define WORLD_H

#include "nest.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Nest;

class World {
  int width, height, energy = 0, penergy = 0, uenergy = 1;

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

  int get_default_energy() const { return energy; }

  int get_default_penergy() const { return penergy; }

  int get_default_uenergy() const { return uenergy; }

  void set_default_energy(int e);

  void set_default_penergy(int p);

  void set_default_uenergy(int u);

  vector<pair<int, int>> *get_occupied_positions();

  vector<pair<int, int>> *get_empty_positions();
};

#endif
