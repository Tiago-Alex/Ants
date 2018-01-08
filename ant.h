#ifndef ANT_H
#define ANT_H

#include "nest.h"
#include <string>
#include <vector>

using namespace std;

class Nest;

class Ant {
  int x, y, energy, vision_ray, motion_ray;
  static int sequence;
  const int nserie;

  Nest *nest;

public:
  Ant(int x, int y, Nest *n);

  ~Ant();

  int get_energy() const { return energy; }

  int get_x() const { return x; }

  int get_y() const { return y; }

  int get_nserie() const { return nserie; }

  std::string get_info();

  int get_vision_ray() const { return vision_ray; }

  int get_motion_ray() const { return motion_ray; }

  void set_x(int x);

  void set_y(int y);

  void set_energy(int e);

  void set_vision_ray(int v);

  void set_motion_ray(int m);
};

class ExplorerAnt : public Ant {
public:
  ExplorerAnt(int x, int y, Nest *n);
};

class CaregiverAnt : public Ant {
public:
  CaregiverAnt(int x, int y, Nest *n);
};

class VigilantAnt : public Ant {
public:
  VigilantAnt(int x, int y, Nest *n);
};

class BurglarAnt : public Ant {
public:
  BurglarAnt(int x, int y, Nest *n);
};

class SurpriseAnt : public Ant {
public:
  SurpriseAnt(int x, int y, Nest *n);
};

#endif
