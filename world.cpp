#include "misc.h"
#include "world.h"
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

void World::add_nest(Nest *n) { nests.push_back(n); }

Nest *World::get_nest_from_id(int id) {
  for (int i = 0; i < (int)nests.size(); i++) {
    if (nests[i]->get_nserie() == id) {
      return nests[i];
    }
  }
  return NULL;
}
