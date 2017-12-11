#ifndef NEST_H
#define NEST_H

#include "ant.h"
#include "community.h"
#include <string>
#include <vector>

using namespace std;

class Ant;

class Nest {
  int x, y, energy = 0;
  const int nserie;
  static int sequence;

  Community *community;

  vector<Ant *> ants;

public:
  Nest(int x, int y, Community *c);

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_energy() const { return energy; }

  int get_nserie() const { return nserie; }

  string toString() const;

  Community *get_community() { return community; }

  void set_energy(int e);

  void add_to_nest(Ant *a);

  vector<Ant *> get_ants() { return ants; }
};

#endif
