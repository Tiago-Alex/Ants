#include "ant.h"
#include "crumb.h"
#include "misc.h"
#include "rules.h"
#include "world.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <time.h>

using namespace std;

void move_ant(Ant *a, int x, int y) {

  a->set_iterations(a->get_iterations() + 1);

  int old_x = a->get_x();
  int old_y = a->get_y();

  a->set_x(x);
  a->set_y(y);

  int effective_movement = abs(old_x - x) + abs(old_y - y);

  char type = a->get_type();

  switch (type) {
  case 'E':
    a->set_energy(a->get_energy() - (1 + effective_movement));
    break;
  case 'C':
    if (a->get_x() != a->get_nest()->get_x() &&
        a->get_y() != a->get_nest()->get_y()) {
      a->set_energy(a->get_energy() - (1 + effective_movement));
    } else {
      if (a->get_energy() > a->get_nest()->get_energy() &&
          a->get_energy() > 200) {
        int energy = a->get_energy() - 200;
        a->set_energy(energy);
        a->get_nest()->set_energy(energy + a->get_nest()->get_energy());
      } else if (a->get_nest()->get_energy() >
                 a->get_nest()->get_world()->get_default_energy()) {
        int energy = a->get_nest()->get_energy() -
                     a->get_nest()->get_world()->get_default_energy();
        a->get_nest()->set_energy(energy);
        a->set_energy(a->get_energy() + energy);
      } else if ((a->get_energy() < 100) && (a->get_nest()->get_energy() > 1)) {
        a->set_energy(a->get_energy() +
                      a->get_nest()->get_world()->get_default_uenergy());
        a->get_nest()->set_energy(
            a->get_energy() -
            a->get_nest()->get_world()->get_default_uenergy());
      } else if ((a->get_energy() > 100 && a->get_energy() < 200) ||
                 (a->get_nest()->get_energy() > 1)) {
        aprroach_ray(a, a->get_x(), a->get_y(), false);
      }
    }
    break;
  case 'V':
    a->set_energy(a->get_energy() - (1 + effective_movement));
    break;
  case 'A':
    a->set_energy(a->get_energy() - (1 + 2 * effective_movement));
    break;
  case 'S':
    a->set_energy(a->get_energy() - (effective_movement));
    break;
  }
}

void aprroach_ray(Ant *a, int x, int y, bool run_away = false) {

  World *w = a->get_nest()->get_world();

  // Dentro de raio de visao verificar as posições vazias, se estiver vazia
  // armazenar em posições disponiveis
  vector<pair<int, int>> *empty = w->get_empty_positions();

  if (empty->size() > 0) {

    vector<pair<int, int>> available;

    int max_x = a->get_x() + a->get_motion_ray();
    if (max_x > w->get_world_width())
      max_x = w->get_world_width();

    int min_x = a->get_x() - a->get_motion_ray();
    if (min_x < 0)
      min_x = 0;

    int max_y = a->get_y() + a->get_motion_ray();
    if (max_y > w->get_world_width())
      max_y = w->get_world_width();

    int min_y = a->get_y() - a->get_motion_ray();
    if (min_y < 0)
      min_y = 0;

    pair<int, int> coordinates;
    for (int x = min_x; x < max_x; x++) {
      for (int y = min_y; y < max_y; y++) {
        coordinates = make_pair(x, y);
        if ((find(empty->begin(), empty->end(), coordinates) != empty->end()) ==
            true) {
          available.push_back(coordinates);
        }
      }
    }

    if (available.size() > 0) {
      int best = (abs(x - a->get_x()) + (y - a->get_y()));
      // Dentro das posições disponiveis procurar aquela que está mais proxima
      for (int i = 0; i < (int)available.size(); ++i) {
        int v = (abs(x - available[i].first) + (y - available[i].second));
        if (run_away) {
          if (v > best) {
            best = v;
          }
        } else {
          if (v < best) {
            best = v;
          }
        }
        coordinates = available[i];
      }
      if (best != (abs(x - a->get_x()) + (y - a->get_y())))
        move_ant(a, coordinates.first, coordinates.second);
    }
  }
}

void EatCrumbRule(Ant *a) {
  char type = a->get_type();
  vector<Crumb *> crumbs = a->get_nest()->get_world()->get_crumbs();
  int energy = 0;
  int max_energy = 0;
  Crumb *c;
  bool touched = false;

  for (int k = 0; k < (int)crumbs.size(); ++k) {
    // variavel para saber se a energia da migalha é superior à próxima migalha
    if ((a->get_x() == crumbs[k]->get_x() &&
         a->get_y() == crumbs[k]->get_y()) ||
        (a->get_x() == (crumbs[k]->get_x() + 1) &&
         a->get_y() == crumbs[k]->get_y()) ||
        (a->get_x() == (crumbs[k]->get_x() - 1) &&
         a->get_y() == crumbs[k]->get_y()) ||
        (a->get_x() == crumbs[k]->get_x() &&
         a->get_y() == (crumbs[k]->get_y() + 1)) ||
        (a->get_x() == crumbs[k]->get_x() &&
         a->get_y() == (crumbs[k]->get_y() - 1))) {
      if (crumbs[k]->get_energy() > max_energy) {
        max_energy = crumbs[k]->get_energy();
        c = crumbs[k];
        touched = true;
      }
    }
  }
  if (touched) {
    switch (type) {
    case 'E':
      energy = 0.1 * c->get_energy();
      a->set_energy(a->get_energy() + energy);
      c->set_energy(c->get_energy() - energy);
      break;

    case 'C':
      energy = 0.5 * c->get_energy();
      a->set_energy(a->get_energy() + energy);
      c->set_energy(c->get_energy() - energy);
      break;

    case 'V':
      energy = 0.75 * c->get_energy();
      a->set_energy(a->get_energy() + energy);
      c->set_energy(c->get_energy() - energy);
      break;

    case 'A':
      energy = 0.75 * c->get_energy();
      a->set_energy(a->get_energy() + energy);
      c->set_energy(c->get_energy() - energy);
      break;

    case 'S':
      energy = 0.85 * c->get_energy();
      a->set_energy(a->get_energy() + energy);
      c->set_energy(c->get_energy() - energy);
      break;
    }
  }
}

void RunRule(Ant *a) {
  World *w = a->get_nest()->get_world();
  vector<Nest *> nests = w->get_nests();

  for (int i = 0; i < (int)nests.size(); ++i) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); ++j) {
      if (ants[j]->get_nest()->get_community() !=
          a->get_nest()->get_community()) {
        int range = a->get_vision_ray();
        if ((check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                         (ants[j]->get_x() + range)) &&
             check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                         (ants[j]->get_y() + range))) == true) {
          aprroach_ray(a, ants[j]->get_x(), ants[j]->get_y(), true);
          break;
        }
      }
    }
  }
}

void ChasesRule(Ant *a) {
  int max_energy = 0;
  World *w = a->get_nest()->get_world();
  pair<int, int> aux;
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); ++i) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); ++j) {
      if (ants[j]->get_nest()->get_community() !=
          a->get_nest()->get_community()) {
        int range = a->get_vision_ray();
        if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
                                        (ants[j]->get_x() + range)) &&
            check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
                                        (ants[j]->get_y() + range))) {
          if (ants[j]->get_energy() > max_energy) {
            max_energy = ants[j]->get_energy();
            aux = make_pair(ants[j]->get_x(), ants[j]->get_y());
          }
        }
      }
    }
  }
  aprroach_ray(a, aux.first, aux.second, false);
}

void RobsRule(Ant *a) {
  int max_energy = 0;
  bool touched = false;
  World *w = a->get_nest()->get_world();
  Ant *rob;
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); ++i) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); ++j) {
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

void ProtectRule(Ant *a) {
  World *w = a->get_nest()->get_world();

  pair<int, int> coordinates1;
  pair<int, int> coordinates2;
  bool same_community = false;
  bool another_community = false;

  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); ++i) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); ++j) {
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
  if (same_community)
    if (another_community) {
      int middle_x = abs(coordinates1.first - coordinates2.first) / 2;
      int middle_y = abs(coordinates2.first - coordinates2.first) / 2;
      aprroach_ray(a, middle_x, middle_y, false);
    }
}

void SearchCrumbRule(Ant *a) {
  World *w = a->get_nest()->get_world();

  int max_energy = 0;
  vector<Crumb *> crumbs = w->get_crumbs();
  Crumb *c;
  int touched = false;

  for (int i = 0; i < (int)crumbs.size(); ++i) {
    int range = a->get_vision_ray();
    if ((check_if_number_is_in_range(crumbs[i]->get_x(), a->get_x() + range,
                                     a->get_x() - range) &&
         check_if_number_is_in_range(crumbs[i]->get_y(), a->get_y() + range,
                                     a->get_x() - range)) == true) {

      if (crumbs[i]->get_energy() > max_energy) {
        max_energy = crumbs[i]->get_energy();
        c = crumbs[i];
        touched = true;
      }
    }
  }
  if (touched)
    aprroach_ray(a, c->get_x(), c->get_y(), false);
}

void GoToNestRule(Ant *a) {
  int energy = a->get_energy();
  int initial_energy;
  switch (a->get_type()) {
  case 'E':
    initial_energy = 200;
    break;
  case 'C':
    initial_energy = 100;
    break;
  case 'V':
    initial_energy = 150;
    break;
  case 'A':
    initial_energy = 80;
    break;
  case 'S':
    initial_energy = 120;
    break;
  }

  Nest *nest = a->get_nest();
  int range = a->get_vision_ray();

  pair<int, int> aux(nest->get_x(), nest->get_y());

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
          move_ant(a, nest->get_x(), nest->get_y());
        } else {
          aprroach_ray(a, nest->get_x(), nest->get_y(), false);
        }
      }
    }
  }
}

void RideRule(Ant *a) {
  World *w = a->get_nest()->get_world();

  vector<pair<int, int>> *empty = w->get_empty_positions();

  if (empty->size() > 0) {

    int range = a->get_vision_ray();

    int x = a->get_x();
    int y = a->get_y();

    vector<pair<int, int>> empty_in_range;
    for (int j = 0; j < (int)empty->size(); ++j) {
      if (check_if_number_is_in_range(empty->at(j).first, (x - range),
                                      (x + range)) &&
          check_if_number_is_in_range(empty->at(j).second, (y - range),
                                      (y + range))) {
        empty_in_range.push_back(empty->at(j));
      }
    }
    if (empty_in_range.size() > 0) {
      pair<int, int> random =
          empty_in_range[random_number((int)empty_in_range.size())];
      move_ant(a, random.first, random.second);
    }
  }
}
