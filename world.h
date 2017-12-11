#ifndef WORLD_H
#define WORLD_H

#include "community.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Community;

class World {
  int width, height;

  vector<Community *> communities;

public:
  World(int, int);
  void set_window_size(int, int);

  int get_perc_tocreate_new_ant(int n);

  int get_perc_transfered_to_ant(int n);

  int window_width() { return width; }

  int window_height() { return height; }

  void add_to_world(Community *c);

  vector<Community *> get_communities() { return communities; }
};

#endif
