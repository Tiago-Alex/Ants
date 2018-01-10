#include "misc.h"
#include "nest.h"
#include <iostream>
#include <iterator>
#include <sstream>

int Nest::sequence = 0;

Nest::Nest(int x, int y, World *w) : nserie(sequence++), community(nserie) {
  this->x = x;
  this->y = y;
  this->world = w;
  this->energy = w->get_default_energy();
  this->penergy = w->get_default_penergy();
  this->uenergy = w->get_default_uenergy();

  /* Add nest to the world on nest creation, so the world store his nests */
  world->add_nest(this);
}

Nest::~Nest() {}

string Nest::get_info() const {

  ostringstream os;
  os << "Ninho: " << get_nserie() << endl
     << "\tEnergia: " << get_energy() << endl
     << "\tPosicao: (" << get_x() << "," << get_y() << ")" << endl
     << "\tFormigas: " << ants.size() << endl;
  return os.str();
}

void Nest::add_ant(Ant *a) { ants.push_back(a); }

void Nest::set_energy(int e) { energy = e; }

void Nest::set_penergy(int p) { penergy = p; }

void Nest::set_uenergy(int u) { uenergy = u; }

bool Nest::remove_ant(int a) {
  for (int i = 0; i < (int)ants.size(); i++) {
    if (ants[i]->get_nserie() == a) {
      delete ants[i];
      ants.erase(ants.begin() + i);
      return true;
    }
  }
  return false;
}
