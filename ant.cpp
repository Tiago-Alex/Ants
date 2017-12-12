#include "ant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Ant::sequence = 0;

Ant::Ant(int x, int y, int type, Nest *n) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  this->type = type;
  nest = n;
  /* Add ant to the nest on ant creation, so the nest store his ants */
  nest->add_ant(this);
}

string Ant::toString() {
  ostringstream os;
  os << "Formiga: " << get_nserie() << "Posicao:(" << get_x() << "," << get_y()
     << ")"
     << "Energia: " << get_energy() << endl;
  return os.str();
}
