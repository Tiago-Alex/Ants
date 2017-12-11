#include "community.h"
#include "consola.h"
#include "exploring_ant.h"
#include "misc.h"
#include "world.h"
#include <iostream>

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

  Nest a(2, 2);
  ExploringAnt f(3, 3, &a);

  Nest b(0, 1);

  Community c(&a);

  c.add_to_nests(a);
  c.add_to_nests(b);

  cout << a.toString() << endl;
  cout << b.toString() << endl;
  cout << c.toString() << endl;
  cout << f.toString() << endl;

  vector<Nest> nests = c.get_nests();

  for (int i = 0; i < (int)nests.size(); i++) {
    cout << nests[i].toString() << endl;
  }

  cout << "Digite [help] para ver a lista de comandos disponiveis" << endl
       << endl;
  while (1) {
    getline(cin, cmd);
    handle_command(cmd);
  }

  return 0;
}
