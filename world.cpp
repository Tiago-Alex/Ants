#include "misc.h"
#include "world.h"
#include "community.h"
#include <iostream>

using namespace std;

World::World(int x, int y) {
  width = x;
  height = y;
}

void World::set_window_size(int x, int y) {
  width = x;
  height = y;
}

int World::get_perc_tocreate_new_ant(int n) { return n; }

int World::get_perc_transfered_to_ant(int n) { return n; }

void World::readfromFile() {
  string line;
  ifstream f("FileName.txt");
  if (f.is_open()) {
    while (getline(f, line))
      handle_command(line);
    f.close();
  } else
    cout << "Unable to open file";
}

void World::add_to_communities(Community c) { communities.push_back(c); }
