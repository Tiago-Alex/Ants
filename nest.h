#ifndef NEST_H
#define NEST_H

#include "ant.h"
#include "consola.h"
#include "draw.h"
#include "world.h"
#include <string>
#include <vector>

using namespace std;

class Ant;

class World;

class Nest {
  int x, y, energy = 0, penergy = 0, uenergy = 1;
  const int nserie, community;
  static int sequence;

  vector<Ant *> ants;

  World *world;

public:
  Nest(int x, int y, World *w);

  ~Nest();

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_energy() const { return energy; }

  int get_penergy() const { return penergy; }

  int get_uenergy() const { return uenergy; }

  int get_nserie() const { return nserie; }

  string get_info() const;

  void set_energy(int e);

  void set_penergy(int p);

  void set_uenergy(int u);

  void add_ant(Ant *a);

  vector<Ant *> get_ants() { return ants; }

  void move_ants_with_range(int range, World *w);

  void remove_ant(Ant *a);

  World *get_world() { return world; }

  void create_ant_by_nest_energy(World *w);
};

#endif
