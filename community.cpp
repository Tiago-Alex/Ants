#include "community.h"
#include <iostream>
#include <sstream>

int Community::sequence = 0;

Community::Community(Nest *n) : nserie(sequence++) { nest = n; }

const Nest *Community::getNest() const { return nest; }

string Community::toString() const {
  ostringstream os;
  os << "Comunidade: " << getNSerie() << nest->toString() << endl;
  return os.str();
}

void Community::add_to_nests(Nest n) { nests.push_back(n); }

void Community::set_energy_nest(int e) {
  for (int i = 0; i < (int)nests.size(); i++)
    nests[i].setEnergia(e);
}
