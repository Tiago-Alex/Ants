#include "ant.h"
#include "misc.h"
#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  string cmd;
  World *world = new World(30, 120);

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    handle_command(cmd, world);
  }

  return 0;
}
