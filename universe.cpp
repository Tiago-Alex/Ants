#include "universe.h"
#include <iostream>

using namespace std;

Universe::Universe() { cout << "Universo criado" << endl; }

void Universe::add_world(World *w, string name) {
  pair<World *, string> world(w, name);
  worlds.push_back(world);
}

void Universe::delete_world(string name) {
  pair<World *, string> to_delete;
  for (int i = 0; i < (int)worlds.size(); ++i) {
    if (name == worlds[i].second) {
      delete worlds[i].first;
      worlds.erase(worlds.begin() + i);
    }
  }
}
