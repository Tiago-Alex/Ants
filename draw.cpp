#include "consola.h"
#include "draw.h"
#include <iostream>

using namespace std;

COORD GetConsoleCursorPosition() {
  static const HANDLE hOut =
      GetStdHandle(STD_OUTPUT_HANDLE); // vai buscar o conteudo da consola

  COORD coord;

  CONSOLE_SCREEN_BUFFER_INFO cbsi;
  if (GetConsoleScreenBufferInfo(hOut, &cbsi)) {
    coord = cbsi.dwCursorPosition;
    return coord;
  } else {
    // The function failed. Call GetLastError() for details.
    COORD invalid = {0, 0};
    return invalid;
  }
}

void redraw_world(World *w) {
  Consola::clrscr();
  draw_world(w);
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    draw(nests[i]->get_x(), nests[i]->get_y(), "*", w);
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      draw(ants[j]->get_x(), ants[j]->get_y(), "#", w);
    }
  }
}

void draw(int x, int y, const char *c, World *w) {
  COORD coord = GetConsoleCursorPosition();
  int height = (int)coord.Y;
  Consola::gotoxy(x + 1, y + 1);
  cout << c;
  Consola::gotoxy(0, height);
}

void draw_world(World *w) {
  int x = w->get_world_width();
  int y = w->get_world_height();
  for (int i = 1; i < x + 1; i++) {
    Consola::gotoxy(i, 0);
    cout << "-";
    Consola::gotoxy(i, y + 1);
    cout << "-";
  }
  for (int i = 1; i < y + 1; i++) {
    Consola::gotoxy(0, i);
    cout << "|";
    Consola::gotoxy(x + 1, i);
    cout << "| " << i;
  }
  Consola::gotoxy(0, y + 4);
}
