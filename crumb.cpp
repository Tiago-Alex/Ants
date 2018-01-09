#include "crumb.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int Crumb::sequence = 0;

Crumb::Crumb(int x, int y, World *w) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  this->world = w;
  energy = w->get_default_energy();
  world->add_crumb(this); // Adicionar migalha ao mundo!
}

Crumb::~Crumb() {
  world->remove_crumb(this);
}

void Crumb::set_energy(int e) { energy = e; }

string Crumb::get_info() const {
  ostringstream os;
  os << "Migalha: " << get_nserie() << endl
     << "Energia: " << get_energy() << endl
     << "Posicao: (" << get_x() << "," << get_y() << ")" << endl;
  return os.str();
}
