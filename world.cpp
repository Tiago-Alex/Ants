#include "misc.h"
#include "world.h"
#include <algorithm>
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

vector<pair<int, int>> *World::get_occupied_positions() {
  vector<pair<int, int>> *occupied = new vector<pair<int, int>>();
  for (int i = 0; i < (int)nests.size(); i++) {
    occupied->push_back(make_pair(nests[i]->get_x(), nests[i]->get_y()));
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      occupied->push_back(make_pair(ants[j]->get_x(), ants[j]->get_y()));
    }
  }
  return occupied;
}

vector<pair<int, int>> *World::get_empty_positions() {
  vector<pair<int, int>> *empty = new vector<pair<int, int>>();
  vector<pair<int, int>> *occupied = get_occupied_positions();
  for (int x = 0; x < get_world_width(); x++) {
    for (int y = 0; y < get_world_height(); y++) {
      pair<int, int> coordinates(x, y);
      if ((find(occupied->begin(), occupied->end(), coordinates) !=
           occupied->end()) == false) {
        empty->push_back(coordinates);
      }
    }
  }
  return empty;
}
