#include "nest.h"
#include <iostream>
#include <sstream>

int Nest::sequence = 0;

Nest::Nest(int x, int y, World *w) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  world = w;
  /* Add nest to the world on nest creation, so the world store his nests */
  world->add_nest(this);
}

string Nest::toString() const {
  ostringstream os;
  os << "Ninho: " << get_nserie() << "Energia: " << get_energy() << "Posicao:("
     << get_x() << "," << get_y() << ")" << endl;
  return os.str();
}

void Nest::add_ant(Ant *a) { ants.push_back(a); }

void Nest::set_energy(int e) { energy = e; }
