#include "main.h"
#include "misc.h"
#include "nest.h"
#include "string.h"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

bool define_nests_energy(int energy, World *w) {
  vector<Nest *> nests = w->get_nests();
  if (nests.size() > 0) {
    for (int i = 0; i < (int)nests.size(); i++) {
      nests[i]->set_energy(energy);
    }
    return true;
  } else {
    cout << "Nao existem ninhos" << endl;
    return false;
  }
}

bool define_nests_penergy(int penergy, World *w) {
  if (penergy >= 0 && penergy <= 100) {
    vector<Nest *> nests = w->get_nests();
    if (nests.size() > 0) {
      for (int i = 0; i < (int)nests.size(); i++) {
        nests[i]->set_penergy(penergy);
      }
      return true;
    } else {
      cout << "Nao existem ninhos" << endl;
      return false;
    }
  } else {
    cout << "A percentagem deve estar compreendida entre 0 e 100" << endl;
    return false;
  }
}

bool define_nests_uenergy(int uenergy, World *w) {
  vector<Nest *> nests = w->get_nests();
  if (nests.size() > 0) {
    for (int i = 0; i < (int)nests.size(); i++) {
      nests[i]->set_uenergy(uenergy);
    }
    return true;
  } else {
    cout << "Nao existem ninhos" << endl;
    return false;
  }
}

bool check_args(vector<string> arg, int n) {
  if ((int)arg.size() < n) {
    cout << "Argumentos em falta" << endl;
    return false;
  }
  return true;
}

bool list_nest(World *w, int key) {
  Nest *nest = w->get_nest_from_id(key);
  if (nest != NULL) {
    cout << nest->get_info() << endl;
    return true;
  } else {
    cout << "Ninho nao encontrado" << endl;
    return false;
  }
}

bool list_position(int x, int y, World *w) {
  vector<Nest *> nests = w->get_nests();
  if (nests.size() > 0) {
    for (int i = 0; i < (int)nests.size(); i++) {
      if (nests[i]->get_x() == x && nests[i]->get_y() == y) {
        cout << nests[i]->get_info() << endl;
      }
      vector<Ant *> ants = nests[i]->get_ants();
      for (int j = 0; j < (int)ants.size(); j++) {
        if (ants[j]->get_x() == x && ants[j]->get_y() == y) {
          cout << ants[j]->get_info() << endl;
        }
      }
    }
    return true;
  } else {
    cout << "Nao existem ninhos" << endl;
    return false;
  }
}

void list_world(World *w) { cout << w->get_elements() << endl; }

vector<string> split_string_into_vector(string str) {
  vector<string> result;
  istringstream ss(str);
  string token;

  while (getline(ss, token, ' ')) {
    result.push_back(token);
  }
  return result;
}

int random_number_in_range(int nMin, int nMax) {
  return nMin + (int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
}

bool create_ant(World *w, const char *type, int n) {
  if (strcmp(type, "E") == 0) {
    Nest *nest = w->get_nest_from_id(n);
    if (nest != NULL) {
      /* For now I'm generating a random number from a given range, I'll
       * change this to put the available coordinates on a vector and select a
       * random vector position */
      new Ant(random_number_in_range(0, w->get_window_width()),
              random_number_in_range(0, w->get_window_height()), type, nest);
      cout << "Formiga criada com sucesso" << endl << endl;
      return true;
    } else
      cout << "Ninho nao encontrado" << endl;
    return false;
  } else {
    cout << "Tipo de formiga invalido" << endl;
    return false;
  }
}

bool define_world_size(int size, World *w) {
  if (size >= 10) {
    w->set_window_size(size, size);
    return true;
  } else {
    cout << "O limite deve ser obrigatoriamente >= 10" << endl;
    return false;
  }
}

void help() {
  cout << endl << "Comandos disponiveis : " << endl << endl;
  cout << endl << "Fase de simulacao" << endl << endl;
  cout << "\tdefmundo <limite> -> Define a dimensao do mundo como uma grelha "
          "bidimensional. Limite >=10"
       << endl;
  cout << "\tdefen <energia> -> Define o valor inicial de energia dos ninhos"
       << endl;
  cout << "\tdefpc <valor> -> Define a percetagem de energia inicial do ninho"
       << endl;
  cout << "\texecuta <nomeFicheiro> -> Le comandos a partir de um ficheiro de "
          "texto"
       << endl;
  cout << "\tinicio -> Se todos os parametros da configuracao foram executados "
          "termina a configuracao e passa a execucao"
       << endl;
  cout << endl << "Fase de simulacao" << endl << endl;
  cout << "\tninho <linha> <coluna> -> cria um ninho" << endl;
  cout << "\tcriaf <F> <T> <N> -> cria formigas" << endl;
  cout << "\ttempo -> avanca uma iteracao" << endl;
  cout << "\tlistamundo -> lista elementos do mundo" << endl;
  cout << "\tlistaninho <N> -> lista toda a informacao relacionada com o ninho"
       << endl;
  cout << "\tlistaposicao <linha> <coluna> -> lista toda a informacao "
          "\trelacionada com a posicao"
       << endl;
  cout << endl << "sair -> termina o programa" << endl << endl;
}

void start(World *w) {
  handle_command("executa comands.txt", w);
  handle_command("defmundo 20", w);
  handle_command("defen 100", w);
  handle_command("defpc 50", w);
  handle_command("defvt 1", w);
}

void handle_command(string cmd, World *w) {

  vector<string> arg = split_string_into_vector(cmd);

  if (arg[0] == "executa") {
    if (check_args(arg, 2)) {
      read_commands_from_file(arg[1], w);
    }
  } else if (arg[0] == "defmundo") {
    if (check_args(arg, 2)) {
      define_world_size(stoi(arg[1]), w);
    }
  } else if (arg[0] == "defen") {
    if (check_args(arg, 2)) {
      define_nests_energy(stoi(arg[1]), w);
    }
  } else if (arg[0] == "defpc") {
    if (check_args(arg, 2)) {
      define_nests_penergy(stoi(arg[1]), w);
    }
  } else if (arg[0] == "defvt") {
    if (check_args(arg, 2)) {
      define_nests_uenergy(stoi(arg[1]), w);
    }
  } else if (arg[0] == "inicio") {
    start(w);
  } else if (arg[0] == "ninho") {
    /* Send the world as parameter so the nest know his world */
    new Nest(stoi(arg[1]), stoi(arg[2]), w);
    cout << "Ninho criado com sucesso" << endl << endl;
  } else if (arg[0] == "criaf") {
    if (check_args(arg, 4)) {
      /*arg[1] -> F formigas
      arg[2] -> T tipo
      arg[3] -> N Ninho
      nota: posições aleatorias vazias */
      for (int i = 0; i < stoi(arg[1]); i++)
        create_ant(w, arg[2].c_str(), stoi(arg[3]));
    }
  } else if (arg[0] == "tempo") {
    cout << arg[1] << endl;
  } else if (arg[0] == "listamundo") {
    list_world(w);
  } else if (arg[0] == "listaninho") {
    if (check_args(arg, 2))
      list_nest(w, stoi(arg[1]));
  } else if (arg[0] == "listaposicao") {
    if (check_args(arg, 2))
      list_position(stoi(arg[1]), stoi(arg[2]), w);
  } else if (arg[0] == "sair") {
    cout << "Programa terminado!" << endl;
    exit(0);
  } else if (arg[0] == "help") {
    help();
  } else {
    cout << cmd << " : Comando nao reconhecido" << endl << endl;
  }
}

void read_commands_from_file(string filename, World *w) {
  ifstream file(filename);

  if (file.is_open()) {

    string comand;
    while (getline(file, comand)) {
      cout << comand << endl;
      handle_command(comand, w);
    }
  } else {
    cout << "Nao foi possivel abrir o ficheiro" << endl;
  }
}
