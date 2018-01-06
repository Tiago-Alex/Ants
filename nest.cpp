#include "misc.h"
#include "nest.h"
#include <iostream>
#include <iterator>
#include <sstream>

int Nest::sequence = 0;

Nest::Nest(int x, int y, World *w) : nserie(sequence++), community(sequence++) {
  this->x = x;
  this->y = y;
  this->world = w;
  this->energy = w->get_default_energy();
  this->penergy = w->get_default_penergy();
  this->uenergy = w->get_default_uenergy();

  /* Add nest to the world on nest creation, so the world store his nests */
  world->add_nest(this);
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
      pair<int, int> random = empty_in_range[random_number((int)empty_in_range.size())];
      ants[i]->set_energy(ants[i]->get_energy() - 1 - (abs(ant_position.first-random.first) + abs(ant_position.second-random.second)));
      ants[i]->set_x(random.first);
      ants[i]->set_y(random.second);
      draw(ant_position.first,ant_position.second," ",w);
      draw(random.first,random.second,"#",w);
    }
  }
}
