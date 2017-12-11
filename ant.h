#ifndef ANT_H
#define ANT_H

#include "nest.h"
#include <string>
#include <vector>

using namespace std;

class Ant {
  int x, y, energy;
  static int sequence;
  const int nserie;

  Nest *nest;

public:
  Ant(int x, int y, Nest *n);

  int getEnergy() const { return energy; }

  int getX() const { return x; }

  int getY() const { return y; }

  int get_nserie() const { return nserie; }

  std::string toString();
};

#endif
