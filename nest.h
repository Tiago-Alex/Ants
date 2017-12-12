#ifndef NEST_H
#define NEST_H

#include "ant.h"
#include "world.h"
#include <string>
#include <vector>

using namespace std;

class Ant;

class World;

class Nest {
  int x, y, energy = 0;
  const int nserie;
  static int sequence;

  vector<Ant *> ants;

  World *world;

public:
  Nest(int x, int y, World *w);

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_energy() const { return energy; }

  int get_nserie() const { return nserie; }

  string toString() const;

  void set_energy(int e);

  void add_ant(Ant *a);

  vector<Ant *> get_ants() { return ants; }
};

#endif
