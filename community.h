#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "ant.h"
#include "nest.h"
#include <string>
#include <vector>

using namespace std;

class Community {
  static int sequence;
  int nserie;
  Nest *nest;

  vector<Ant *> ants;

public:
  Community(Nest *n);
  const Nest *getNest() const;
  string toString() const;
  int get_nserie() const { return nserie; }

  // void set_energy_nest(int e);

  void add_to_ants(Ant *a);

  vector<Ant *> get_ants() { return ants; }
};

#endif
