#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "world.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Universe {
  vector<pair<World *, string>> worlds;

public:
  Universe();

  void add_world(World *w, string name);

  vector<pair<World *, string>> get_worlds() { return worlds; }

  void delete_world(string name);
};

#endif
