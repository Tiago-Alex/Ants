#include "ant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Ant::sequence = 0;

Ant::Ant(int x, int y, const char *type, Nest *n) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  this->type = type;
  nest = n;
  /* Add ant to the nest on ant creation, so the nest store his ants */
  nest->add_ant(this);
}

string Ant::get_info() {
  ostringstream os;
  os << "Formiga: " << get_nserie() << endl
     << "\tPosicao: (" << get_x() << "," << get_y() << ")" << endl
     << "\tEnergia: " << get_energy() << endl;
  return os.str();
}

void Ant::set_x(int x) { this->x = x; }

void Ant::set_y(int y) { this->y = y; }
