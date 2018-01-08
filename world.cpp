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

void World::add_crumb(Crumb *c) { crumbs.push_back(c); }

Nest *World::get_nest_from_id(int id) {
  for (int i = 0; i < (int)nests.size(); i++) {
    if (nests[i]->get_nserie() == id) {
      return nests[i];
    }
  }
  return NULL;
}

Ant *World::get_ant_from_coordinates(int x, int y) {
  for (int j = 0; j < (int)nests.size(); j++) {
    vector<Ant *> ants = nests[j]->get_ants();
    for (int i = 0; i < (int)ants.size(); i++) {
      if (ants[i]->get_x() == x && ants[i]->get_y() == y) {
        return ants[i];
      }
    }
  }
  return NULL;
}

Crumb *World::get_crumb_by_coordinates(int x, int y) {
  for (int i = 0; i < (int)crumbs.size(); i++) {
    if (crumbs[i]->getX() == x && crumbs[i]->getY() == y) {
      return crumbs[i];
    }
  }
  return NULL;
}

const string World::get_elements() {
  for (int j = 0; j < (int)crumbs.size(); j++) {
    cout << crumbs[j]->getInfo();
  }
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

void World::set_default_penergy(int p) { penergy = (p / 100); }

void World::set_default_uenergy(int u) { uenergy = u; }

void World::set_default_cenergy(int c) { cenergy = c; }

void World::set_default_perc_crumbs(int n) { pcrumbs = (int)n / 100; }

vector<pair<int, int>> *World::get_occupied_positions() {
  vector<pair<int, int>> *occupied = new vector<pair<int, int>>();
  for (int i = 0; i < (int)nests.size(); i++) {
    occupied->push_back(make_pair(nests[i]->get_x(), nests[i]->get_y()));
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      occupied->push_back(make_pair(ants[j]->get_x(), ants[j]->get_y()));
    }
  }
  for (int k = 0; k < (int)crumbs.size(); k++)
    occupied->push_back(make_pair(crumbs[k]->getX(), crumbs[k]->getY()));
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

void World::set_configured(string command) { configured.push_back(command); }

void World::remove_nest(Nest *n) {
  nests.erase(nests.begin() + n->get_nserie());
}

void World::remove_crumb(Crumb *c) {
  crumbs.erase(crumbs.begin() + c->get_nserie());
}
