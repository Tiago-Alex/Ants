#include "crumb.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int Crumb::sequence = 0;

Crumb::Crumb(int x, int y, World * w):nserie(sequence++){
  this->x = x;
  this->y = y;
  cenergy = w->get_default_cenergy();
  world->add_crumb(this);   // Adicionar migalha ao mundo!
}

string Crumb::getInfo() const{
  ostringstream os;
    os  << "Migalha: " << get_nserie() << endl
        << "Energia: " << getEnergy()  << endl
        << "Posicao: (" << getX() << "," << getY() << ")" << endl;
  return os.str();
}
