#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <string>
#include <vector>
#include "world.h"

using namespace std;

class World;

class Community {
  static int sequence;
  int nserie;

  World *world;

public:
  Community(World *w);
  string toString() const;
  int get_nserie() const { return nserie; }

  World *get_world() { return world; }
};

#endif
