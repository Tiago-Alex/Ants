#ifndef NEST_H
#define NEST_H

#include <string>
#include <vector>

using namespace std;

class Nest {
  int x, y, energy;
  const int nserie;
  static int sequence;

public:
  Nest(int x, int y);

  int getX() const { return x; }

  int getY() const { return y; }

  int getEnergy() const { return energy; }

  int getNSerie() const { return nserie; }

  void setEnergia(int e);

  string toString() const;
};

#endif
