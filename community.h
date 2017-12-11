#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "nest.h"
#include <string>
#include <vector>

using namespace std;

class Community {
  static int sequence;
  int nserie;
  Nest *nest;

  vector<Nest> nests;

public:
  Community(Nest *n);
  const Nest *getNest() const;
  string toString() const;
  int getNSerie() const { return nserie; }

  void add_to_nests(Nest n);

  vector<Nest> get_nests() { return nests; }

  void set_energy_nest(int e);
};

#endif
