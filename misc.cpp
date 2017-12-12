#include "main.h"
#include "nest.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void list_nest(World *w, int key) {
  Nest *nest = w->get_nest_from_id(key);
  cout << nest->toString() << endl;
}

void list_world(World *w) {
  vector<Nest *> n = w->get_nests();
  for (int i = 0; i < (int)n.size(); i++) {
    cout << endl << "Ninho : " << n[i]->get_nserie() << endl << endl;
  }
}

vector<string> split_string_into_vector(string str) {
  vector<string> result;
  istringstream ss(str);
  string token;

  while (getline(ss, token, ' ')) {
    result.push_back(token);
  }
  return result;
}

void handle_command(string cmd, World *w) {

  vector<string> arg = split_string_into_vector(cmd);

  if (arg[0] == "ninho") {
    /* Send the world as parameter so the nest know his world */
    new Nest(stoi(arg[1]), stoi(arg[2]), w);
    cout << "Ninho criado com sucesso" << endl << endl;
  } else if (arg[0] == "criaf") {
    /*arg[1] -> F formigas
    arg[2] -> T tipo
    arg[3] -> N Ninho
    nota: posições aleatorias vazias */
    Nest *n = new Nest(stoi(arg[1]), stoi(arg[2]), w);
    new Ant(stoi(arg[1]), stoi(arg[2]), 1, n);
    cout << "Formiga criada com sucesso" << endl << endl;
  } else if (arg[0] == "tempo") {
    cout << arg[1] << endl;
  } else if (arg[0] == "listamundo") {
    list_world(w);
    cout << "Mundo listado com sucesso" << endl << endl;
  } else if (arg[0] == "listaninho") {
    list_nest(w, stoi(arg[1]));
    cout << "Ninho listado com sucesso" << endl;
  } else if (arg[0] == "listaposicao") {
    cout << arg[1] << endl;
  } else if (arg[0] == "sair") {
    cout << "Programa terminado!" << endl;
    exit(0);
  } else if (arg[0] == "help") {
    cout << endl << "Comandos disponiveis : " << endl << endl;
    cout << "ninho -> cria um ninho" << endl;
    cout << "criaf -> cria formigas" << endl;
    cout << "tempo -> avanca uma iteracao" << endl;
    cout << "listamundo -> lista elementos do mundo" << endl;
    cout << "listaninho -> lista toda a informacao relacionada com o ninho"
         << endl;
    cout << "listaposicao -> lista toda a informacao relacionada com a posicao"
         << endl;
    cout << "sair -> termina o programa" << endl << endl;
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
