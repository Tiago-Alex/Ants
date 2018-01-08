#include "rules.h"
#include "ant.h"
#include "world.h"
#include "crumb.h"
#include <iostream>
using namespace std;
class World;
class Ant;
class Crumb;


void EatCrumbRule(char type, World *w) {
  type = tolower(type);
  vector<Nest *> nest = w->get_nests();
  vector<Crumb *> crumbs = w->get_crumbs();

  for(int i = 0; i < (int)nest.size(); i++) {
    vector<Ant *> ants = nest[i]->get_ants();
      for(int j = 0; j < (int)ants.size(); j++){
        for(int k = 0; k < (int)crumbs.size(); k++) {
          int aux = crumbs[k]->getEnergy();  //variavel para saber se a energia da migalha é superior à próxima migalha
          if(ants[j]->get_x() == crumbs[j]->getX() && ants[j]->get_y() == crumbs[j]->getY() && aux > crumbs[k++]->getEnergy()) {
            switch(type) {
              case 'e':   ants[j]->set_energy(ants[j]->get_energy() + 0.1*crumbs[k]->getEnergy()); //do tipo exploadora, retira 10% da energia da migalha
                          crumbs[k]->set_cenergy(crumbs[k]->getEnergy() / 0.2);
                          break;
              case 'c':   ants[j]->set_energy(ants[j]->get_energy() + 0.5*crumbs[k]->getEnergy());  //do tipo cuidadora, retira 50% da energia da migalha
                          crumbs[k]->set_cenergy(crumbs[k]->getEnergy() / 0.2);
                          break;
              case 'v':   ants[j]->set_energy(ants[j]->get_energy() + 0.75*crumbs[k]->getEnergy()); //do tipo vigilante, retira 75% da energia da migalha
                          crumbs[k]->set_cenergy(crumbs[k]->getEnergy() / 0.2);
                          break;
              case 'a':   ants[j]->set_energy(ants[j]->get_energy() + 0.5*crumbs[k]->getEnergy()); //do tipo assaltante, retira 25% da energia da migalha
                          crumbs[k]->set_cenergy(crumbs[k]->getEnergy() / 0.2);
                          break;
              default:    break;
            }
          }
        }
      }
  }
}

void RunRule(World *w) {
vector<Nest *> nests = w->get_nests();
for(int i = 0; i < (int)nests.size(); i++) {
  vector<Ant *> ants = nests[i]->get_ants();
    for(int j = 0; j < (int)ants.size(); j++) {
    }
  }
}
