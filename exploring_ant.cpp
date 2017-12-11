#include "exploring_ant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int ExploringAnt::sequence = 0;

ExploringAnt::ExploringAnt(int x, int y, Nest *n)
    : nserie(sequence++), nest(n) {
  this->x = x;
  this->y = y;
  energy = 100;
}

string ExploringAnt::toString() {
  ostringstream os;
  os << "Formiga Exploradora: " << getNserie() << "Posicao:(" << getX() << ","
     << getY() << ")"
     << "Energia: " << getEnergy() << nest->toString() << endl;
  return os.str();
}
