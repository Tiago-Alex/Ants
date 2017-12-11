#include "community.h"
#include <iostream>
#include <sstream>

int Community::sequence = 0;

Community::Community(World *w) : nserie(sequence++) {
  world = w;
  world->add_to_world(this);
}

string Community::toString() const {
  ostringstream os;
  os << "Comunidade: " << get_nserie() << endl;
  return os.str();
}
