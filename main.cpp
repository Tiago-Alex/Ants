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
  World w(30, 120);

  Consola::setTextSize(10, 10);
  Consola::setScreenSize(w.window_width(), w.window_height());
  Consola::setBackgroundColor(Consola::AZUL);
  Consola::setTextColor(Consola::AMARELO_CLARO);
  Consola::clrscr();
  cin.ignore(cin.rdbuf()->in_avail());

  Nest *a = new Nest(2, 2);
  Nest *b = new Nest(1, 0);

  Ant *z = new Ant(3, 3, a);
  Ant *x = new Ant(2, 0, a);
  Ant *v = new Ant(1, 2, a);

  Community *c = new Community(a);

  c->add_to_ants(z);
  c->add_to_ants(x);
  c->add_to_ants(v);

  cout << a->toString() << endl;
  cout << b->toString() << endl;
  cout << c->toString() << endl;

  vector<Ant *> ants = c->get_ants();

  for (int i = 0; i < (int)ants.size(); i++)
    cout << "Ant ->" << ants[i]->get_nserie() << endl;

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    handle_command(cmd);
  }

  return 0;
}
