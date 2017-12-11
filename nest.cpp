#include "nest.h"
#include <iostream>
#include <sstream>

int Nest::sequence = 0;

Nest::Nest(int x, int y) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  energy = 100;
}

void Nest::setEnergia(int e) { energy = e; }

string Nest::toString() const {
  ostringstream os;
  os << "Ninho: " << getNSerie() << "Energia: " << getEnergy() << "Posicao:("
     << getX() << "," << getY() << ")" << endl;
  return os.str();
}
