#include "consola.h"
#include "draw.h"
#include "main.h"
#include "misc.h"
#include "nest.h"
#include "string.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <time.h>
#include <vector>

bool check_if_number_is_in_range(int number, unsigned int min, unsigned int max) {
  if ((unsigned)(number - min) <= (max - min)) {
    return true;
  } else {
    return false;
  }
}

bool move_ants(World *w) {
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    nests[i]->move_ants_with_range(8,w);
  }
  return true;
}

bool define_nests_energy(int energy, World *w) {
  w->set_default_energy(energy);
  return true;
}

bool define_nests_penergy(int penergy, World *w) {
  w->set_default_penergy(penergy);
  return true;
}

bool define_nests_uenergy(int uenergy, World *w) {
  w->set_default_uenergy(uenergy);
  return true;
}

bool define_nests_cenergy(int cenergy, World * w) {
  w->set_default_cenergy(cenergy);
  return true;
}

bool define_perc_of_crumbs(int n, World *w){
  if(n > 0){
    w->set_default_perc_crumbs(n);
    return true;
  } else{
      cout << "valor invalido" << endl;
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

void list_ants(World *w) {
  vector<Nest *> nests = w->get_nests();
  for (int i = 0; i < (int)nests.size(); i++) {
    vector<Ant *> ants = nests[i]->get_ants();
    for (int j = 0; j < (int)ants.size(); j++) {
      cout << ants[j]->get_info() << endl;
    }
  }
}

int random_number(int max) {
  srand(time(NULL));

  return rand() % max + 0;
}

bool create_ant(World *w, const char *type, int n) {
  if (strcmp(type, "E") == 0) {
    Nest *nest = w->get_nest_from_id(n);
    if (nest != NULL) {

      /* How we know empty positions -> we create a vector of pairs(widht,
height) of all occupied positions, we run a cicle of all possible coordinates
according to the widht*height and we check if the coordinate is occupied, if
not we add it to a vector of pairs called the empty positions, next we
randomize a number from the index of the vector and select from there */

      vector<pair<int, int>> *empty = w->get_empty_positions();
      pair<int, int> random = empty->at(random_number((int)empty->size()));
      new ExplorerAnt(random.first, random.second, nest);
      draw(random.first, random.second, "#", w);
      return true;
    } else
      cout << "Ninho nao encontrado" << endl;
    return false;
  } else {
    cout << "Tipo de formiga invalido" << endl;
    return false;
  }
}

bool create_nest(int x, int y, World *w) {
  pair<int, int> coordinates(x, y);
  vector<pair<int, int>> *occupied = w->get_occupied_positions();
  if ((find(occupied->begin(), occupied->end(), coordinates) != occupied->end()) == false) {
    if (y <= w->get_world_width() && x <= w->get_world_height()) {
      new Nest(x, y, w);
      draw(x, y, "*", w);
      return true;
    } else {
      cout << "Coordenadas invalidas" << endl;
      return false;
    }
  } else {
    cout << "Essa posicao ja esta ocupada" << endl;
    return false;
  }
}

bool create_crumb(int x, int y, World *w){
  pair<int,int> coordinates(x,y);
  vector<pair<int, int>> *occupied = w->get_occupied_positions();
  if ((find(occupied->begin(), occupied->end(), coordinates) != occupied->end()) == false){
    if (y < w->get_world_width() && x < w->get_world_height()) {
      new Crumb(x,y,w);
      draw(x,y,"M",w);
      return true;
    } else{
      cout << "Coordenadas invalidsa!" << endl;
      return false;
    }
  } else {
    cout << "Essa posicao ja esta ocupada" << endl;
    return false;
  }
}

bool define_world_size(int size, World *w) {
  if (size >= 10) {
    w->set_world_size(size, size);
    return true;
  } else {
    cout << "O limite deve ser obrigatoriamente >= 10" << endl;
    return false;
  }
}

bool configured(World *w) {
  vector<string> configured = w->get_configured();
  if (find(configured.begin(), configured.end(), "defmundo") !=
          configured.end() &&
      (find(configured.begin(), configured.end(), "defen") !=
           configured.end() &&
       (find(configured.begin(), configured.end(), "defpc") !=
            configured.end() &&
        find(configured.begin(), configured.end(), "defvt") !=
            configured.end() &&
        find(configured.begin(), configured.end(), "defmi") !=
                configured.end() &&
        find(configured.begin(), configured.end(), "defme") !=
                configured.end() &&
        find(configured.begin(), configured.end(), "inicio") !=
            configured.end())))
    return true;
  else
    return false;
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
  cout << "\tinicio -> Se todos os parametros da configuracao foram "
          "executados "
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

bool configuration(vector<string> arg, World *w) {
  if (arg[0] == "defmundo") {
    if (check_args(arg, 2)) {
      if (define_world_size(stoi(arg[1]), w)) {
        w->set_configured("defmundo");
      }
    }
  } else if (arg[0] == "defen") {
    if (check_args(arg, 2)) {
      if (define_nests_energy(stoi(arg[1]), w)) {
        w->set_configured("defen");
      }
    }
  } else if (arg[0] == "defpc") {
    if (check_args(arg, 2)) {
      if (define_nests_penergy(stoi(arg[1]), w)) {
        w->set_configured("defpc");
      }
    }
  } else if (arg[0] == "defvt") {
    if (check_args(arg, 2)) {
      if (define_nests_uenergy(stoi(arg[1]), w)) {
        w->set_configured("defvt");
      }
    }
  } else if (arg[0] == "defmi") {
    if (check_args(arg, 2)) {
      if (stoi(arg[1]) < 0)
        cout << "Valor invalido" << endl;
      else {
        define_perc_of_crumbs(stoi(arg[1]),w);
        w->set_configured("defmi");
      }
    }
  } else if (arg[0] == "defme"){
    if (check_args(arg,2)) {
      if (define_nests_cenergy(stoi(arg[1]),w)) {
        w->set_configured("defme");
      }
    }
  }
    else if (arg[0] == "inicio") {
    w->set_configured("inicio");
    if (configured(w)) {
      cout << "Configuracao concluida" << endl;
      Consola::clrscr();
      draw_world(w);
    } else
      cout << "O mundo nao esta totalmente configurado" << endl;
  } else {
    return false;
  }
  return true;
}

bool simulation(vector<string> arg, World *w) {
  if (arg[0] == "ninho") {
    if (check_args(arg, 3)) {
      return create_nest(stoi(arg[1]), stoi(arg[2]), w);
    }
  } else if (arg[0] == "criaf") {
    if (check_args(arg, 4)) {
      for (int i = 0; i < stoi(arg[1]); i++) {
        create_ant(w, arg[2].c_str(), stoi(arg[3]));
      }
    }
  } else if (arg[0] == "migalha"){
    if (check_args(arg,3)) {
      return create_crumb(stoi(arg[1]), stoi(arg[2]), w);
    }
  } else if (arg[0] == "energninho") {
    vector<Nest *> nests = w->get_nests();
    if (check_args(arg,3)) {
      for(int i = 0; i < (int)nests.size(); i++){
        if (stoi(arg[1]) == nests[i]->get_nserie())
          nests[i]->set_energy(nests[i]->get_energy() + stoi(arg[2]));
      }
    }
  } else if (arg[0] == "energformiga") {
    vector<Nest *> nests = w->get_nests();
    if (check_args(arg, 4)) {
      for(int i = 0; i < (int)nests.size(); i++){
        vector<Ant *> ants = nests[i]->get_ants();
        for(int j = 0; j < (int)ants.size(); j++){
          if (stoi(arg[1]) == ants[j]->get_x() && stoi(arg[2]) == ants[j]->get_y())
            ants[j]->set_energy(ants[j]->get_energy() + stoi(arg[3]));
          }
      }
    }
  } else if(arg[0] == "mata") {
    if (check_args(arg, 3)) {
      if(w->remove_ant(stoi(arg[1]),stoi(arg[2]),w) == true)
        cout << "Formiga eliminado com sucesso!" << endl;
      else
        cout << "Erro a eliminar formiga" << endl;
      }
  } else if (arg[0] == "inseticida"){
    if (check_args(arg, 2)) {
      if(w->remove_nest(stoi(arg[1]),w) == true)
        cout << "Ninho eliminado com sucesso!" << endl;
      else
        cout << "Erro a eliminar ninho" << endl;
      }
  } else if (arg[0] == "tempo") {  // uma iteração de cada vez
    move_ants(w);
  } else if(arg[0] == "tempo") {  // várias iterações de uma vez só
    if (check_args(arg,2)) {
      for(int i = 0; i < stoi(arg[1]); i++)
        move_ants(w);
    }
  } else if (arg[0] == "listamundo") {
    list_world(w);
  } else if (arg[0] == "listaninho") {
    if (check_args(arg, 2))
      list_nest(w, stoi(arg[1]));
  } else if (arg[0] == "listaformigas") {
    list_ants(w);
  } else if (arg[0] == "listaposicao") {
    if (check_args(arg, 3))
      list_position(stoi(arg[1]), stoi(arg[2]), w);
  } else if (arg[0] == "apaga") {
    if (check_args(arg, 2)){
      if (arg[1] == "commands.txt"){
         if (remove("commands.txt" ) != 0 )
          perror( "Error deleting file" );
        else{
          puts( "File successfully deleted" );
          system("cls");
          main();           // PARA VOLTAR À FASE DE CONFIGURACAO
        }
      }
    }
  } else if (arg[0] == "guarda"){  // está a guarda em binario
      if (check_args(arg, 2)){
        ofstream file;
        file.open(arg[1]);
        file.write((char*)(&w), sizeof(World));
        file.close();
      }
  } else {                                          // FALTA GUARDAR E MUDAR UMA CÓPIA DO MUNDO!
    return false;
  }
  return true;
}

void additional_commands(vector<string> arg, World *w) {
  if (arg[0] == "executa") {
    if (check_args(arg, 2)) {
      read_commands_from_file(arg[1], w);
    }
  } else if (arg[0] == "sair") {
    cout << "Programa terminado!" << endl;
    exit(0);
  } else if (arg[0] == "help") {
    help();
  } else {
    cout << arg[0] << " : Comando nao reconhecido" << endl;
  }
}

bool handle_command(string cmd, World *w) {

  vector<string> arg = split_string_into_vector(cmd);

  if (configured(w) == false) {
    if (!configuration(arg, w))
      additional_commands(arg, w);
  } else {
    if (!simulation(arg, w))
      additional_commands(arg, w);
  }
  return true;
}

bool read_commands_from_file(string filename, World *w) {
  ifstream file(filename);

  if (file.is_open()) {

    string comand;
    while (getline(file, comand)) {
      cout << comand << endl;
      handle_command(comand, w);
    }
    return true;
  } else {
    cout << "Nao foi possivel abrir o ficheiro" << endl;
    return false;
  }
}
