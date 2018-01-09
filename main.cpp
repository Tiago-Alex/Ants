#include "ant.h"
#include "consola.h"
#include "misc.h"
#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  string cmd;
  World *world = new World(30, 30);

  Consola::clrscr();

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    if (cmd != "") {
      handle_command(cmd, world);
    }
  }

  return 0;
}
