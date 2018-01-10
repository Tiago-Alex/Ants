#include "ant.h"
#include "crumb.h"
#include "misc.h"
#include "rules.h"
#include "world.h"
#include <algorithm>
#include <iostream>

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
        a->get_y() != a->get_nest()->get_y())
      a->set_energy(a->get_energy() - (1 + effective_movement));
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
            crumbs[k]->set_energy(crumbs[k]->get_energy() -
                                  ants[j]->get_energy());
            break;
          case 'c':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.5 * crumbs[k]->get_energy()); // do tipo
                                                                // cuidadora,
                                                                // retira 50% da
                                                                // energia da
                                                                // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() -
                                  ants[j]->get_energy());
            break;
          case 'v':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.75 *
                                    crumbs[k]->get_energy()); // do tipo
                                                              // vigilante,
                                                              // retira 75% da
                                                              // energia da
                                                              // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() -
                                  ants[j]->get_energy());

            break;
          case 'a':
            ants[j]->set_energy(ants[j]->get_energy() +
                                0.5 * crumbs[k]->get_energy());
            // do tipo
            // assaltante,
            // retira 25% da
            // energia da
            // migalha
            crumbs[k]->set_energy(crumbs[k]->get_energy() -
                                  ants[j]->get_energy());
            break;
          default:
            break;
          }
          if (crumbs[k]->get_energy() <
              0.1 * w->get_default_cenergy()) { // Se tiver menos que 10% da
                                                // energia inicial desaparece
            delete crumbs[k];
          }
        }
      }
    }
  }
}

// void RunRule(World *w, Ant *a) {
//   vector<Nest *> nests = w->get_nests();
//   for (int i = 0; i < (int)nests.size(); i++) {
//     vector<Ant *> ants = nests[i]->get_ants();
//     for (int j = 0; j < (int)ants.size(); j++) {
//       if (ants[j]->get_nest()->get_community() ==
//           a->get_nest()->get_community()) {
//         int range = a->get_vision_ray();
//         if ((check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() -
//         range),
//                                          (ants[j]->get_x() + range)) &&
//              check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() -
//              range),
//                                          (ants[j]->get_y() + range))) ==
//                                          true) {
//           if (a->get_x() ==
//               ants[i]->get_x()) { // Se tiverem no mesmo eixo dos xx
//             int x = rand() % a->get_x() -
//                     a->get_motion_ray(); // Valor random entre a
//                                          // coordenada actual e o seu raio
//                                          // de movimento
//
//             if (x <= w->get_world_width() &&
//                 x >= 0) // Verificacao se a operacao anterior
//                         // fica fora da grelha do mundo
//               move_ant(a, x, a->get_y());
//             else if (x < 0)
//               move_ant(a, x, a->get_y());
//             else
//               move_ant(a, w->get_world_width(), a->get_y());
//
//           } else if (a->get_y() ==
//                      ants[i]->get_y()) { // Se tiverem no mesmo eixo dos yy
//             int y = rand() % a->get_y() - a->get_motion_ray();
//             if (y <= w->get_world_height())
//               move_ant(a, a->get_x(), 0);
//             else
//               a->set_y(y);
//           } else {
//             ants[i]->set_x(rand() % ants[i]->get_x() -
//                            ants[i]->get_motion_ray()); // Se tiver na
//                            diagonal
//             ants[i]->set_y(rand() % ants[i]->get_y() -
//                            ants[i]->get_motion_ray());
//           }
//         }
//       }
//     }
//   }
// }

// void ChasesRule(World *w, Ant *a) {
//   int max_energy = 0;
//   vector<pair<int, int>> *occupied = w->get_occupied_positions();
//   pair<int, int> aux;
//   vector<Nest *> nests = w->get_nests();
//   for (int i = 0; i < (int)nests.size(); i++) {
//     vector<Ant *> ants = nests[i]->get_ants();
//     for (int j = 0; j < (int)ants.size(); j++) {
//       if (ants[j]->get_nest()->get_community() !=
//           a->get_nest()->get_community()) {
//         int range = a->get_vision_ray();
//         if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() -
//         range),
//                                         (ants[j]->get_x() + range)) &&
//             check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() -
//             range),
//                                         (ants[j]->get_y() + range))) {
//           if (ants[j]->get_energy() > max_energy) {
//             max_energy = ants[j]->get_energy();
//             aux = make_pair(ants[j]->get_x(), ants[j]->get_y());
//           }
//         }
//       }
//     }
//   }
//   if (aux.first == a->get_x()) {             // Se tiverem no mesmo eixo dos
//   xx
//     int x = rand() % aux.first + a->get_x(); // Valor random entre a
//     coordenada
//                                              // actual e o seu raio de
//                                              movimento
//     if (x <= w->get_world_width() &&
//         (find(occupied->begin(), occupied->end(), x) != occupied->end()) ==
//             false) // Verificacao se a operacao anterior fica fora da grelha
//             do
//                    // mundo
//       a->set_x(0); // se ficar fora a formiga fica com os xx a 0
//     else
//       a->set_x(x);
//   } else if (aux.second == a->get_y()) { // Se tiverem no mesmo eixo dos yy
//     int x = rand() % aux.second + a->get_y();
//     if (x <= w->get_world_height() && (find(occupied->begin(),
//     occupied->end(),
//                                             x) != occupied->end()) == false)
//       a->set_y(0);
//     else
//       a->set_y(x);
//   } else {
//     a->set_x(rand() % aux.first + a->get_x()); // Se tiver na diagonal
//     a->set_y(rand() % aux.second + a->get_y());
//   }
// }

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

// void ProtectRule(World *w, Ant *a) {
//   pair<int, int> coordinates1;
//   pair<int, int> coordinates2;
//   vector<pair<int, int>> *occupied = w->get_occupied_positions();
//   bool same_community = false;
//   bool another_community = false;
//   vector<Nest *> nests = w->get_nests();
//   for (int i = 0; i < (int)nests.size(); i++) {
//     vector<Ant *> ants = nests[i]->get_ants();
//     for (int j = 0; j < (int)ants.size(); j++) {
//       int range = a->get_vision_ray();
//       if (check_if_number_is_in_range(a->get_x(), (ants[j]->get_x() - range),
//                                       (ants[j]->get_x() + range)) &&
//           check_if_number_is_in_range(a->get_y(), (ants[j]->get_y() - range),
//                                       (ants[j]->get_y() + range))) {
//         if (ants[j]->get_nest()->get_community() ==
//             a->get_nest()->get_community()) {
//           same_community = true;
//           coordinates1 = make_pair(ants[j]->get_x(), ants[j]->get_y());
//         } else {
//           another_community = true;
//           coordinates2 = make_pair(ants[j]->get_x(), ants[j]->get_y());
//         }
//       }
//     }
//   }
//   if (same_community)
//     if (another_community) {
//       if (coordinates1.first == coordinates2.first &&
//           coordinates1.second <
//               coordinates2
//                   .second) { // Se a formiga inimiga e a formiga aliada
//                              // estiverem no eixo dos xx e se a formiga
//                              // aliada estiver do lado esquerdo à da inimiga
//         int x = rand() % coordinates2.first +
//                 coordinates1.first; // valor random do x da formiga aliada
//                 ate
//                                     // ao x da formiga inimiga
//         if ((find(occupied->begin(), occupied->end(), x) != occupied->end())
//         ==
//             false)
//           a->set_x(x);
//       } else if (coordinates1.first == coordinates2.first &&
//                  coordinates1.second > coordinates2.second) {
//         int x = rand() % coordinates1.first + coordinates2.first;
//         if ((find(occupied->begin(), occupied->end(), x) != occupied->end())
//         ==
//             false)
//           a->set_y(x);
//       } else if (coordinates1.second == coordinates2.second &&
//                  coordinates1.first > coordinates2.first) {
//         int x = rand() % coordinates2.second + coordinates1.second;
//         if ((find(occupied->begin(), occupied->end(), x) != occupied->end())
//         ==
//             false)
//           a->set_y(x);
//       } else if (coordinates1.second == coordinates2.second &&
//                  coordinates1.first < coordinates2.first) {
//         int x = rand() % coordinates2.second + coordinates1.second;
//         if ((find(occupied->begin(), occupied->end(), x) != occupied->end())
//         ==
//             false)
//           a->set_y(x);
//       } else {
//         int aux_x = rand() % coordinates2.first + coordinates1.first;
//         int aux_y = rand() % coordinates2.second + coordinates2.first;
//         if ((find(occupied->begin(), occupied->end(), aux_x) !=
//              occupied->end()) == false &&
//             (find(occupied->begin(), occupied->end(), aux_y) !=
//              occupied->end()) == false) {
//           a->set_x(aux_x);
//           a->set_y(aux_y);
//         }
//       }
//     }
// }

// void SearchCrumbRule(World *w, Ant *a) {
//   int max_energy = 0;
//   vector<pair<int, int>> *occupied = w->get_occupied_positions();
//   vector<Nest *> nests = w->get_nests();
//   vector<Crumb *> crumbs = w->get_crumbs();
//   pair<int, int> aux;
//
//   for (int i = 0; i < (int)nests.size(); i++) {
//     vector<Ant *> ants = nests[i]->get_ants();
//     for (int j = 0; j < (int)ants.size(); j++) {
//       for (int k = 0; k < (int)crumbs.size(); k++) {
//         int range = ants[i]->get_vision_ray();
//         if ((check_if_number_is_in_range(crumbs[k]->get_x(),
//                                          ants[j]->get_x() + range,
//                                          ants[j]->get_x() - range) &&
//              check_if_number_is_in_range(crumbs[k]->get_y(),
//                                          ants[j]->get_y() + range,
//                                          ants[j]->get_x() - range)) == true)
//                                          {
//
//           if (crumbs[k]->get_energy() > max_energy) {
//             max_energy = crumbs[k]->get_energy();
//             aux = make_pair(crumbs[k]->get_x(), crumbs[k]->get_y());
//           }
//         }
//       }
//     }
//   }
//   if (aux.first == a->get_x()) {             // Se tiverem no mesmo eixo dos
//   xx
//     int x = rand() % aux.first + a->get_x(); // Valor random entre a
//     coordenada
//                                              // actual e o seu raio de
//                                              movimento
//     if (x <= w->get_world_width() &&
//         (find(occupied->begin(), occupied->end(), x) != occupied->end()) ==
//             false) // Verificacao se a operacao anterior fica fora da grelha
//             do
//                    // mundo
//       a->set_x(0); // se ficar fora a formiga fica com os xx a 0
//     else
//       a->set_x(x);
//   } else if (aux.second == a->get_y()) { // Se tiverem no mesmo eixo dos yy
//     int x = rand() % aux.second + a->get_y();
//     if (x <= w->get_world_height() && (find(occupied->begin(),
//     occupied->end(),
//                                             x) != occupied->end()) == false)
//       a->set_y(0);
//     else
//       a->set_y(x);
//   } else {
//     a->set_x(rand() % aux.first + a->get_x()); // Se tiver na diagonal
//     a->set_y(rand() % aux.second + a->get_y());
//   }
// }

// void GoToNestRule(World *w, Ant *a) {
//   int energy = a->get_energy();
//   int initial_energy = 100;
//   Nest *nest = a->get_nest();
//   int range = a->get_vision_ray();
//
//   vector<pair<int, int>> *occupied = w->get_occupied_positions();
//
//   pair<int, int> aux(nest->get_x(), nest->get_y());
//
//   if (energy > initial_energy || energy < initial_energy / 2) {
//     if (check_if_number_is_in_range(a->get_x(), (nest->get_x() - range),
//                                     (nest->get_x() + range)) &&
//         check_if_number_is_in_range(a->get_y(), (nest->get_y() - range),
//                                     (nest->get_y() + range))) {
//       if (a->get_iterations() > 10) {
//         // Se o ninho estiver no raio de movimento, entra no ninho
//         range = a->get_motion_ray();
//         if (check_if_number_is_in_range(a->get_x(), (nest->get_x() - range),
//                                         (nest->get_x() + range)) &&
//             check_if_number_is_in_range(a->get_y(), (nest->get_y() - range),
//                                         (nest->get_y() + range))) {
//           a->set_x(nest->get_x());
//           a->set_y(nest->get_y());
//         } else {
//           if (aux.first == a->get_x()) { // Se tiverem no mesmo eixo dos xx
//             int x = rand() % aux.first +
//                     a->get_x(); // Valor random entre a coordenada
//                                 // actual e o seu raio de movimento
//             if (x <= w->get_world_width() &&
//                 (find(occupied->begin(), occupied->end(), x) !=
//                  occupied->end()) == false) // Verificacao se a operacao
//                                             // anterior fica fora da grelha
//                                             do
//                                             // mundo
//               a->set_x(0); // se ficar fora a formiga fica com os xx a 0
//             else
//               a->set_x(x);
//           } else if (aux.second ==
//                      a->get_y()) { // Se tiverem no mesmo eixo dos yy
//             int x = rand() % aux.second + a->get_y();
//             if (x <= w->get_world_height() &&
//                 (find(occupied->begin(), occupied->end(), x) !=
//                  occupied->end()) == false)
//               a->set_y(0);
//             else
//               a->set_y(x);
//           } else {
//             a->set_x(rand() % aux.first + a->get_x()); // Se tiver na
//             diagonal a->set_y(rand() % aux.second + a->get_y());
//           }
//         }
//       }
//     }
//   }
// }

void RideRule(World *w, Ant *a) {
  vector<pair<int, int>> *empty = w->get_empty_positions();

  int range = a->get_vision_ray();

  int x = a->get_x();
  int y = a->get_y();

  vector<pair<int, int>> empty_in_range;
  for (int j = 0; j < (int)empty->size(); j++) {
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
