#include "ant.h"
#include "consola.h"
#include "misc.h"
#include "world.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  string cmd;
  World *world = new World(30, 120);

  Consola::setTextSize(10, 10);
  Consola::setScreenSize(world->get_window_width(), world->get_window_height());
  Consola::setBackgroundColor(Consola::AZUL);
  Consola::setTextColor(Consola::AMARELO_CLARO);
  Consola::clrscr();
  cin.ignore(cin.rdbuf()->in_avail());

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    handle_command(cmd, world);
  }

  return 0;
}
