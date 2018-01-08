#ifndef CRUMB_H
#define CRUMB_H

#include "world.h"
#include <iostream>
#include <string>

using namespace std;
class World;

class Crumb { // Migalha
  int x, y, cenergy;
  const int nserie;
  static int sequence;

  World *world;

public:
  Crumb(int x, int y, World *w);
  ~Crumb();
  int get_energy() const { return cenergy; }
  int get_x() const { return x; }
  int get_y() const { return y; }
  int get_nserie() const { return nserie; }
  void set_cenergy(int e);
  string get_info() const;
};
#endif
