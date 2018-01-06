#ifndef WORLD_H
#define WORLD_H

#include "ant.h"
#include "nest.h"
#include "crumb.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
class Ant;

class Crumb;

class Nest;

class World {
  int width, height, energy = 0, penergy = 0, uenergy = 1, cenergy = 0;

  vector<Nest *> nests;
  vector<Crumb *> crumbs;

  vector<string> configured;

public:
  World(int x, int y);
  void set_world_size(int x, int y);

  int get_world_width() { return width; }

  int get_world_height() { return height; }

  vector<Nest *> get_nests() { return nests; }

  void add_nest(Nest *n);

  void add_crumb(Crumb *c);

  Nest *get_nest_from_id(int id);

  Ant *get_ant_from_coordinates(int x,int y, World *w);

  const string get_elements();

  int get_default_energy() const { return energy; }

  int get_default_penergy() const { return penergy; }

  int get_default_uenergy() const { return uenergy; }

  int get_default_cenergy() const { return cenergy; }

  void set_default_energy(int e);

  void set_default_penergy(int p);

  void set_default_uenergy(int u);

  void set_default_cenergy(int c);

  vector<pair<int, int>> *get_occupied_positions();

  vector<pair<int, int>> *get_empty_positions();

  void set_configured(string command);

  vector<string> get_configured() const { return configured; }

  bool remove_ant(int x, int y, World *w);

  bool remove_nest(int n);
};

#endif
