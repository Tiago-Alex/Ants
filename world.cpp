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

void World::add_crumb(Crumb *c) {crumbs.push_back(c); }

Nest *World::get_nest_from_id(int id) {
  for (int i = 0; i < (int)nests.size(); i++) {
    if (nests[i]->get_nserie() == id) {
      return nests[i];
    }
  }
  return NULL;
}

Ant *World::get_ant_from_coordinates(int x,int y, World *w) {
  vector<Nest *> nests = w->get_nests();
  for(int j = 0; j < (int)nests.size(); j++){
    vector<Ant *> ants = nests[j]->get_ants();
    for (int i = 0; i < (int)ants.size(); i++) {
      if (ants[i]->get_x() == x && ants[i]->get_y() == y) {
        return ants[i];
      }
    }
  }
  return NULL;
}

const string World::get_elements() {
  //falta adicionar as infos das migalhas
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

void World::set_default_cenergy(int c) { cenergy = c;}

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

bool World::remove_ant(int x, int y, World *w){
        Ant * ant = get_ant_from_coordinates(x,y,w);
        delete ant;
        return true;
  }

bool World::remove_nest(int n){
      Nest * nest = get_nest_from_id(n);
      delete nest;
      return true;
  }

void World::set_configured(string command) {
  configured.push_back(command);
}
