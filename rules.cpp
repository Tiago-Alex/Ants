#include "ant.h"
#include "crumb.h"
#include "misc.h"
#include "rules.h"
#include "world.h"
#include <iostream>
using namespace std;
class World;
class Ant;
class Crumb;

// Check
void EatCrumbRule(char type, World *w) {
  type = tolower(type);
  vector<Nest *> nest = w->get_nests();
  vector<Crumb *> crumbs = w->get_crumbs();

  for (int i = 0; i < (int)nest.size(); i++) {
    vector<Ant *> ants = nest[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      for (int k = 0; k < (int)crumbs.size(); k++) {
        int aux =
            crumbs[k]->get_energy(); // variavel para saber se a energia da
                                     // migalha é superior à próxima migalha
        if (ants[j]->get_x() == crumbs[j]->get_x() &&
            ants[j]->get_y() == crumbs[j]->get_y() &&
            aux > crumbs[k++]->get_energy()) {
          switch (type) {
          case 'e':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.1 * crumbs[k]->get_energy()); // do tipo
                                                                // exploadora,
                                                                // retira 10% da
                                                                // energia da
                                                                // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() / 0.2);
            break;
          case 'c':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.5 * crumbs[k]->get_energy()); // do tipo
                                                                // cuidadora,
                                                                // retira 50% da
                                                                // energia da
                                                                // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() / 0.2);
            break;
          case 'v':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.75 *
                                    crumbs[k]->get_energy()); // do tipo
                                                              // vigilante,
                                                              // retira 75% da
                                                              // energia da
                                                              // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() / 0.2);
            break;
          case 'a':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.5 * crumbs[k]->get_energy()); // do tipo
                                                                // assaltante,
                                                                // retira 25% da
                                                                // energia da
                                                                // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() / 0.2);
            break;
          default:
            break;
          }
        }
      }
    }
  }
}

// Check
void RunRule(World *w, Ant *a) {
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      if (ants[j]->get_nest()->get_community() ==
          a->get_nest()->get_community()) {
        int range = a->get_vision_ray();
        if ((check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                         (ants[j]->get_x() + range)) &&
             check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                         (ants[j]->get_y() + range))) == true) {
          if (a->get_x() ==
              ants[i]->get_x()) { // Se tiverem no mesmo eixo dos xx
            if (a->get_x() > ants[i]->get_x())
              ants[i]->set_x(ants[i]->get_x() + 1); // Anda uma célula para trás
            else
              ants[i]->set_x(ants[i]->get_x() - 1); // Anda uma célula para trás
          } else if (a->get_y() ==
                     ants[i]->get_y()) { // Se tiverem no mesmo eixo dos yy
            if (a->get_y() > ants[i]->get_y())
              ants[i]->set_y(ants[i]->get_y() + 1); // Anda uma célula para trás
            else
              ants[i]->set_y(ants[i]->get_y() - 1); // Anda uma célula para trás
          } else {
            ants[i]->set_x(ants[i]->get_x() - 1); // Se tiverem na diagonal
            ants[i]->set_y(ants[i]->get_y() - 1);
          }
        }
      }
    }
  }
}

// Check
void ChasesRule(World *w, Ant *a) {
  int max_energy = 0;
  pair<int, int> coordinates;
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      if (ants[j]->get_nest()->get_community() !=
          a->get_nest()->get_community()) {
        int range = a->get_vision_ray();
        if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                        (ants[j]->get_x() + range)) &&
            check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                        (ants[j]->get_y() + range))) {
          if (ants[j]->get_energy() > max_energy) {
            max_energy = ants[j]->get_energy();
            coordinates = make_pair(ants[j]->get_x(), ants[j]->get_y());
          }
        }
      }
    }
  }
  if (a->get_x() == coordinates.first) { // Se tiverem no mesmo eixo dos xx
    a->set_x(coordinates.first - 1);     // Anda uma célula para trás
  } else if (a->get_y() ==
             coordinates.second) { // Se tiverem no mesmo eixo dos yy
    a->set_y(coordinates.second - 1);
  } else {
    a->set_x(coordinates.first - 1); // Se tiverem na diagonal
    a->set_y(coordinates.second - 1);
  }
}

// Check
void RobsRule(World *w, Ant *a) {
  int max_energy = 0;
  bool touched = false;
  Ant *rob;
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      if (ants[j]->get_nest()->get_community() !=
          a->get_nest()->get_community()) {
        int range = a->get_motion_ray();
        if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                        (ants[j]->get_x() + range)) &&
            check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                        (ants[j]->get_y() + range))) {
          if (ants[j]->get_energy() > max_energy) {
            max_energy = ants[j]->get_energy();
            rob = ants[j];
            touched = true;
          }
        }
      }
    }
  }
  if (touched) {
    int energy = rob->get_energy();
    rob->set_energy(energy / 2);
    a->set_energy(a->get_energy() + energy / 2);
  }
}

void ProtectRule(World *w, Ant *a) {
  pair<int, int> coordinates1;
  pair<int, int> coordinates2;
  bool same_community = false;
  bool another_community = false;
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      int range = a->get_vision_ray();
      if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                      (ants[j]->get_x() + range)) &&
          check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                      (ants[j]->get_y() + range))) {
        if (ants[j]->get_nest()->get_community() ==
            a->get_nest()->get_community()) {
          same_community = true;
          coordinates1 = make_pair(ants[j]->get_x(), ants[j]->get_y());
        } else {
          another_community = true;
          coordinates2 = make_pair(ants[j]->get_x(), ants[j]->get_y());
        }
      }
    }
  }
  if (same_community && another_community)
      cout << "ok";
  /* TODO : Mover para uma posição intermedia entre as duas*/
}

void SearchCrumbRule(World *w, Ant *a) {
  int max_energy = 0;
  Crumb *c;
  vector<Crumb *> crumbs = w->get_crumbs();
  for (int i = 0; i < (int)crumbs.size(); i++) {
    int range = a->get_vision_ray();
    if (check_if_number_is_in_range(a->get_x(), (crumbs[i]->get_x() - range),
                                    (crumbs[i]->get_x() + range)) &&
        check_if_number_is_in_range(a->get_y(), (crumbs[i]->get_y() - range),
                                    (crumbs[i]->get_y() + range))) {
      if (crumbs[i]->get_energy() > max_energy) {
        max_energy = crumbs[i]->get_energy();
        c = crumbs[i];
      }
    }
  }
  // TODO:
  delete c;
}

// Check
void GoToNestRule(World *w, Ant *a) {
  int energy = a->get_energy();
  int initial_energy = 100;
  Nest *nest = a->get_nest();
  int range = a->get_vision_ray();

  if (energy > initial_energy || energy < initial_energy / 2) {
    if (check_if_number_is_in_range(a->get_x(), (nest->get_x() - range),
                                    (nest->get_x() + range)) &&
        check_if_number_is_in_range(a->get_y(), (nest->get_y() - range),
                                    (nest->get_y() + range))) {
      if (a->get_iterations() > 10) {
        // Se o ninho estiver no raio de movimento, entra no ninho
        range = a->get_motion_ray();
        if (check_if_number_is_in_range(a->get_x(), (nest->get_x() - range),
                                        (nest->get_x() + range)) &&
            check_if_number_is_in_range(a->get_y(), (nest->get_y() - range),
                                        (nest->get_y() + range))) {
          a->set_x(nest->get_x());
          a->set_y(nest->get_y());
        } else {
          // if (a->get_x() == nest->get_x()) { // Se tiverem no mesmo eixo dos xx
          //   a->set_x(nest->get_x() - 1);     // Anda uma célula para trás
          // } else if (a->get_y() ==
          //            nest->get_y()) { // Se tiverem no mesmo eixo dos yy
          //   a->set_y(nest->get_y() - 1);
          // } else {
          //   a->set_x(nest->get_x() - 1); // Se tiverem na diagonal
          //   a->set_y(nest->get_y() - 1);
          // }
        }
      }
    }
  }
}

void RideRule() {}
