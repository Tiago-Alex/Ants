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

void refresh_world(World *w) {
  Consola::clrscr();
  draw_world(w);
  vector<Nest *> nests = w->get_nests();
  vector<Crumb *> crumbs = w->get_crumbs();
  for (int i = 0; i < (int)crumbs.size(); i++) {
    draw(crumbs[i]->get_x(), crumbs[i]->get_y(), "M", w, 0);
  }
  for (int i = 0; i < (int)nests.size(); i++) {
    int color = nests[i]->get_community() + 1;
    draw(nests[i]->get_x(), nests[i]->get_y(), "N", w, color);
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      char type = ants[j]->get_type();
      switch (type) {
      case 'E':
        if (ants[j]->get_energy() > 50)
          draw(ants[j]->get_x(), ants[j]->get_y(), "E", w, color);
        else
          draw(ants[j]->get_x(), ants[j]->get_y(), "e", w, color);
        break;
      case 'C':
        if (ants[j]->get_energy() > 50)
          draw(ants[j]->get_x(), ants[j]->get_y(), "C", w, color);
        else
          draw(ants[j]->get_x(), ants[j]->get_y(), "c", w, color);
        break;
      case 'V':
        if (ants[j]->get_energy() > 50)
          draw(ants[j]->get_x(), ants[j]->get_y(), "V", w, color);
        else
          draw(ants[j]->get_x(), ants[j]->get_y(), "v", w, color);
        break;
      case 'A':
        if (ants[j]->get_energy() > 50)
          draw(ants[j]->get_x(), ants[j]->get_y(), "A", w, color);
        else
          draw(ants[j]->get_x(), ants[j]->get_y(), "a", w, color);
        break;
      case 'S':
        if (ants[j]->get_energy() > 50)
          draw(ants[j]->get_x(), ants[j]->get_y(), "S", w, color);
        else
          draw(ants[j]->get_x(), ants[j]->get_y(), "s", w, color);
        break;
      }
    }
  }
}

void draw(int x, int y, const char *c, World *w, int color) {
  Consola::setBackgroundColor(color);
  COORD coord = GetConsoleCursorPosition();
  int height = (int)coord.Y;
  Consola::gotoxy(x + 1, y + 1);
  cout << c;
  Consola::gotoxy(0, height);
  Consola::setBackgroundColor(0);
}

void draw_world(World *w) {
  int x = w->get_world_width();
  int y = w->get_world_height();
  for (int i = 1; i < x + 1; i++) {
    Consola::gotoxy(i, 0);
    cout << "-";
    Consola::gotoxy(i, y + 1);
    cout << "-";

    Consola::gotoxy(i, y + 2);
    if (i % 2 == 0)
      Consola::setBackgroundColor(7);
    else
      Consola::setBackgroundColor(8);
    Consola::setTextColor(0);
    char numero[2];
    sprintf(numero, "%d", i - 1);
    if (i - 1 >= 10) {
      cout << numero[0];
      Consola::gotoxy(i, y + 3);
      cout << numero[1];
      Consola::gotoxy(i, y + 2);
    } else {
      cout << numero[0];
      Consola::gotoxy(i, y + 3);
      cout << " ";
      Consola::gotoxy(i, y + 2);
    }
    Consola::setBackgroundColor(0);
    Consola::setTextColor(7);
  }
  for (int i = 1; i < y + 1; i++) {
    Consola::gotoxy(0, i);
    cout << "|";
    Consola::gotoxy(x + 1, i);
    cout << "|";
    if (i % 2 == 0)
      Consola::setBackgroundColor(7);
    else
      Consola::setBackgroundColor(8);
    Consola::setTextColor(0);
    if (i - 1 >= 10)
      cout << i - 1;
    else
      cout << i - 1 << " ";
    Consola::setBackgroundColor(0);
    Consola::setTextColor(7);
  }
  Consola::gotoxy(0, y + 5);
}
