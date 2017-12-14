#include "misc.h"
#include "world.h"
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

World::World(int x, int y) {
  width = x;
  height = y;
}

void World::set_world_size(int x, int y) {
  width = x;
  height = y;
}

void World::add_nest(Nest *n) { nests.push_back(n); }

Nest *World::get_nest_from_id(int id) {
  for (int i = 0; i < (int)nests.size(); i++) {
    if (nests[i]->get_nserie() == id) {
      return nests[i];
    }
  }
  return NULL;
}

const string World::get_elements() {

  vector<string> nests_list;
  for (int i = 0; i < (int)nests.size(); i++) {
    nests_list.push_back(nests[i]->get_info());
  }
  ostringstream ss;

  copy(nests_list.begin(), nests_list.end(),
       ostream_iterator<string>(ss, "\n"));

  return ss.str();
}

void World::set_default_energy(int e) { energy = e; }

void World::set_default_penergy(int p) { penergy = p; }

void World::set_default_uenergy(int u) { uenergy = u; }
