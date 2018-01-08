#include "ant.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Ant::sequence = 0;

Ant::Ant(int x, int y, Nest *n) : nserie(sequence++) {
  this->x = x;
  this->y = y;
  nest = n;
  /* Add ant to the nest on ant creation, so the nest store his ants */
  nest->add_ant(this);
}

Ant::~Ant() {
  nest->remove_ant(this);
  draw(x, y, " ", nest->get_world());
}

string Ant::get_info() {
  ostringstream os;
  os << "Formiga: " << get_nserie() << endl
     << "\tPosicao: (" << get_x() << "," << get_y() << ")" << endl
     << "\tEnergia: " << get_energy() << endl;
  return os.str();
}

void Ant::set_x(int x) { this->x = x; }

void Ant::set_y(int y) { this->y = y; }

void Ant::set_energy(int e) { energy = e; }

void Ant::set_vision_ray(int v) { vision_ray = v; }

void Ant::set_motion_ray(int m) { motion_ray = m; }

ExplorerAnt::ExplorerAnt(int x, int y, Nest *n) : Ant(x, y, n) {
  set_energy(200);
  set_vision_ray(10);
  set_motion_ray(8);
}

CaregiverAnt::CaregiverAnt(int x, int y, Nest *n) : Ant(x, y, n) {
  set_energy(100);
  set_vision_ray(5);
  set_motion_ray(3);
}

VigilantAnt::VigilantAnt(int x, int y, Nest *n) : Ant(x, y, n) {
  set_energy(150);
  set_vision_ray(7);
  set_motion_ray(5);
}

BurglarAnt::BurglarAnt(int x, int y, Nest *n) : Ant(x, y, n) {
  set_energy(80);
  set_vision_ray(8);
  set_motion_ray(4);
}

SurpriseAnt::SurpriseAnt(int x, int y, Nest *n) : Ant(x, y, n) {
  set_energy(120);
  set_vision_ray(10);
  set_motion_ray(8);
}
