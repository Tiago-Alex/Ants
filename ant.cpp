#include "ant.h"
#include "nest.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Ant::sequence = 0;

Ant::Ant(int x, int y, Nest *n) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  energy = 100;
  nest = n;

}

string Ant::toString() {
  ostringstream os;
  os << "Formiga: " << get_nserie() << "Posicao:(" << getX() << "," << getY()
     << ")"
     << "Energia: " << getEnergy() << endl;
  return os.str();
}
