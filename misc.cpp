#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split_string_into_vector(string str) {
  vector<string> result;
  istringstream ss(str);
  string token;

  while (std::getline(ss, token, ' ')) {
    result.push_back(token);
  }
  return result;
}

void handle_command(string cmd) {

  vector<string> arg = split_string_into_vector(cmd);

  if (arg[0] == "ninho") {
    cout << arg[1] << endl;
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
