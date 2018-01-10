#ifndef WORLD_H
#define WORLD_H

#include "ant.h"
#include "crumb.h"
#include "nest.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
class Ant;

class Crumb;

class Nest;

class World {
  int width, height, energy = 0, penergy = 0, uenergy = 1, cenergy = 0,
                     pcrumbs = 0, max_crumbs = 0;
  // penergy = percetagem de energia
  // uenergy = unidades de energia
  // pcrumbs = percentagem de migalhas no mundo

  vector<Nest *> nests;
  vector<Crumb *> crumbs;

  vector<string> configured;

public:
  World(int x, int y);
  void set_world_size(int x, int y);

  int get_world_width() { return width; }

  int get_world_height() { return height; }

  vector<Nest *> get_nests() { return nests; }

  vector<Crumb *> get_crumbs() { return crumbs; }

  void add_nest(Nest *n);

  void add_crumb(Crumb *c);

  Nest *get_nest_from_id(int id);

  Ant *get_ant_from_coordinates(int x, int y);

  Crumb *get_crumb_by_coordinates(int x, int y);

  const string get_elements();

  int get_default_energy() const { return energy; }

  int get_default_penergy() const { return penergy; }

  int get_default_uenergy() const { return uenergy; }

  int get_default_cenergy() const { return cenergy; }

  int get_perc_of_crumbs() const { return pcrumbs; }

  int get_max_crumbs() const { return max_crumbs; }

  void set_default_energy(int e);

  void set_default_penergy(int p);

  void set_default_uenergy(int u);

  void set_default_cenergy(int c);

  void set_default_perc_crumbs(int n);

  vector<pair<int, int>> *get_occupied_positions();

  vector<pair<int, int>> *get_occupied_positions_with_crumbs();

  vector<pair<int, int>> *get_occupied_ants();

  vector<pair<int, int>> *get_empty_positions();

  vector<pair<int, int>> *get_empty_positions_with_crumbs();

  void set_configured(string command);

  vector<string> get_configured() const { return configured; }

  void reset_configuration() { configured.clear(); }

  bool remove_nest(int n);

  bool remove_crumb(int c);

  void set_max_crumbs(int c);
};

#endif
