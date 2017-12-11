#include "nest.h"
#include <iostream>
#include <sstream>

int Nest::sequence = 0;

Nest::Nest(int x, int y, Community *c) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  community = c;
}

string Nest::toString() const {
  ostringstream os;
  os << "Ninho: " << get_nserie() << "Energia: " << get_energy() << "Posicao:("
     << get_x() << "," << get_y() << ")" << endl;
  return os.str();
}

void Nest::add_to_nest(Ant *a) { ants.push_back(a); }

void Nest::set_energy(int e) { energy = e; }
