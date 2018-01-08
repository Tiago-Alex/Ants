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

Nest::~Nest() {
  vector<Ant *> aux = ants;
  for (int i = 0; i < (int)aux.size(); i++) {
    delete aux[i];
  }
  ants.clear();
  world->remove_nest(this);
  draw(x, y, " ", world);
}

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

void Nest::move_ants_with_range(int range, World *w) {
  vector<pair<int, int>> *empty = world->get_empty_positions();
  vector<Crumb *> crumbs = w->get_crumbs();

  for (int j = 0; j < (int)crumbs.size(); j++) {
    crumbs[j]->set_cenergy(
        crumbs[j]->getEnergy() -
        1); // retira 1 unidade de energia a todas as migalhas
    if (crumbs[j]->getEnergy() <
        (0.1 * w->get_default_cenergy())) { // se a energia actual da migalha
                                            // for inferior a 10% da energia
                                            // inicial, desaparece
      draw(crumbs[j]->getX(), crumbs[j]->getY(), " ", w);
      w->remove_crumb(crumbs[j]->getX(), crumbs[j]->getY(), w);
    }
  }

  for (int i = 0; i < (int)ants.size(); i++) {
    pair<int, int> ant_position(ants[i]->get_x(), ants[i]->get_y());
    vector<pair<int, int>> empty_in_range;
    for (int j = 0; j < (int)empty->size(); j++) {
      if (check_if_number_is_in_range(empty->at(j).first,
                                      (ant_position.first - range),
                                      (ant_position.first + range)) &&
          check_if_number_is_in_range(empty->at(j).second,
                                      (ant_position.second - range),
                                      (ant_position.second + range))) {
        empty_in_range.push_back(empty->at(j));
      }
    }
    if (empty_in_range.size() > 0) {
      pair<int, int> random =
          empty_in_range[random_number((int)empty_in_range.size())];
      ants[i]->set_energy(ants[i]->get_energy() - 1 -
                          (abs(ant_position.first - random.first) +
                           abs(ant_position.second - random.second)));
      ants[i]->set_x(random.first);
      ants[i]->set_y(random.second);
      draw(ant_position.first, ant_position.second, " ", w);
      draw(random.first, random.second, "#", w);
    }
  }
}

void Nest::remove_ant(Ant *a) { ants.erase(ants.begin() + a->get_nserie()); }
