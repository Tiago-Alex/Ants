#include "ant.h"
#include "community.h"
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
  Consola::setScreenSize(world->window_width(), world->window_height());
  Consola::setBackgroundColor(Consola::AZUL);
  Consola::setTextColor(Consola::AMARELO_CLARO);
  Consola::clrscr();
  cin.ignore(cin.rdbuf()->in_avail());

  Community *c = new Community(world);

  Nest *a = new Nest(2, 2, c);

  Ant *z = new Ant(3, 3, a);
  Ant *x = new Ant(2, 0, a);
  Ant *v = new Ant(1, 2, a);

  cout << a->toString() << endl;
  cout << c->toString() << endl;
  cout << z->toString() << endl;
  cout << x->toString() << endl;
  cout << v->toString() << endl;

  vector<Ant *> ants = a->get_ants();

  for (int i = 0; i < (int)ants.size(); i++)
    cout << "Ant ->" << ants[i]->get_nserie() << endl;

  read_commands_from_file("commands.txt", world);

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    handle_command(cmd, world);
  }

  return 0;
}
