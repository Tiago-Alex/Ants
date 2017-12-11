#include "ant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Ant::sequence = 0;

Ant::Ant(int x, int y, Nest *n) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  nest = n;
  nest->add_to_nest(this);
}

string Ant::toString() {
  ostringstream os;
  os << "Formiga: " << get_nserie() << "Posicao:(" << get_x() << "," << get_y()
     << ")"
     << "Energia: " << get_energy() << endl;
  return os.str();
}
