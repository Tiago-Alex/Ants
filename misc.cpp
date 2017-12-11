#include "community.h"
#include "main.h"
#include "nest.h"
#include "world.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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
    Community *community = new Community(NULL);
    new Nest(stoi(arg[1]), stoi(arg[2]), community);
  } else if (arg[0] == "criaf") {
    cout << arg[1] << endl;
  } else if (arg[0] == "tempo") {
    cout << arg[1] << endl;
  } else if (arg[0] == "listamundo") {
    cout << arg[1] << endl;
  } else if (arg[0] == "listamundo") {
    cout << arg[1] << endl;
  } else if (arg[0] == "listaninho") {
    cout << arg[1] << endl;
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
         << endl
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
