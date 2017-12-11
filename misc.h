#ifndef MISC_H
#define MISC_H

#include <iostream>
#include <vector>

using namespace std;

vector<string> split_string_into_vector(string str);
void handle_command(string cmd, World *w);

void read_commands_from_file(string filename, World *W);

#endif
