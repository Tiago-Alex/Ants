#ifndef MISC_H
#define MISC_H

#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

void additional_commands(vector<string> arg, World *w);
bool check_args(vector<string> arg, int n);
bool check_if_number_is_in_range(int number, unsigned int min,
                                 unsigned int max);
bool configuration(vector<string> arg, World *w);
bool configured(World *w);
bool create_ant_1(World *w, const char *type, int n, int x, int y);
void create_ant_by_nest_energy(World *w);
bool create_ant(World *w, const char *type, int n);
bool create_crumb(int x, int y, World *w);
bool create_nest(int x, int y, World *w);
void decrease_crumbs_energy(World *w);
bool define_max_crumbs_per_iteration(int c, World *w);
bool define_nests_cenergy(int cenergy, World *w);
bool define_nests_energy(int energy, World *w);
bool define_nests_penergy(int penergy, World *w);
bool define_nests_uenergy(int uenergy, World *w);
bool define_perc_of_crumbs(int n, World *w);
bool define_world_size(int size, World *w);
bool handle_command(string cmd, World *w);
void help();
void iteration(World *w);
void list_ants(World *w);
bool list_nest(World *w, int key);
bool list_position(int x, int y, World *w);
void list_world(World *w);
int random_number(int max);
bool read_commands_from_file(string filename, World *w);
bool remove_ant(int x, int y, World *w);
bool simulation(vector<string> arg, World *w);
void transfer_energy_ant_to_nest(World *w);
void update_crumbs(World *w);

#endif
