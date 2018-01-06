#ifndef MISC_H
#define MISC_H

#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

bool check_if_number_is_in_range(int number, unsigned int min,
                                 unsigned int max);
bool move_ants(World *w);
bool read_commands_from_file(string filename, World *w);
bool handle_command(string cmd, World *w);
bool start(World *w);
void help();
bool define_world_size(int size, World *w);
bool create_nest(int x, int y, World *w);
bool create_ant(World *w, const char *type, int n);
int random_number(int max);
void list_ants(World *w);
vector<string> split_string_into_vector(string str);
void list_world(World *w);
bool list_position(int x, int y, World *w);
bool list_nest(World *w, int key);
bool check_args(vector<string> arg, int n);
bool define_nests_uenergy(int uenergy, World *w);
bool define_nests_penergy(int penergy, World *w);
bool define_nests_energy(int energy, World *w);
bool define_perc_of_crumbs(int n, World *w);

#endif
