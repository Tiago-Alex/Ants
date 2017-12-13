#ifndef MISC_H
#define MISC_H

#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

void read_commands_from_file(string filename, World *w);
void handle_command(string cmd, World *w);
void start(World *w);
void help();
bool define_world_size(int size, World *w);
bool create_ant(World *w, const char *type, int n);
int random_number_in_range(int nMin, int nMax);
vector<string> split_string_into_vector(string str);
void list_world(World *w);
bool list_nest(World *w, int key);
bool check_args(vector<string> arg, int n);
bool define_nests_uenergy(int uenergy, World *w);
bool define_nests_penergy(int penergy, World *w);
bool define_nests_energy(int energy, World *w);

#endif
