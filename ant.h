#ifndef ANT_H
#define ANT_H

#include "nest.h"
#include <string>
#include <vector>

using namespace std;

class Nest;

class Ant {
  int x, y, energy = 200;
  const char *type;
  static int sequence;
  const int nserie;

  Nest *nest;

public:
  Ant(int x, int y, const char *type, Nest *n);

  int get_energy() const { return energy; }

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_nserie() const { return nserie; }

  std::string get_info();

  void set_x(int x);

  void set_y(int y);
};

#endif
