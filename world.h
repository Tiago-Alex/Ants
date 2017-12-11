#ifndef WORLD_H
#define WORLD_H

#include "community.h"
#include "nest.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class World {
  int width, height;

  vector<Community> communities;

public:
  World(int, int);
  void set_window_size(int, int);

  int get_perc_tocreate_new_ant(int n);

  int get_perc_transfered_to_ant(int n);

  void readfromFile();

  int window_width() { return width; }

  int window_height() { return height; }

  void add_to_communities(Community c);

  vector<Community> get_communities() { return communities; }
};

#endif
