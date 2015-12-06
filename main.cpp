#include <fstream>
#include <iostream>
#include <pthread.h>
#include "main.h"

class Machine {
  Conveyor *conveyor;
  pthread_mutex_t *locks;

public:
  void init(Conveyor *conveyor) {
    this -> conveyor = conveyor;
    for(int i = 0; i < conveyor -> getTypesCount(); ++i) {
      pthread_mutex_init(locks[i], NULL)
    }
  }
};

class Conveyor {
  int types_count;
  int machines_count;
  Machine *machines;

  void clearSreen(){
    std::cout << std::endl;
    system("clear");
  }

public:
  int getTypesCount(){
    return types_count;
  }

  Conveyor(int machines_count, int types_count) {
    this -> types_count = types_count;
    this -> machines_count = machines_count;
    this -> machines = new Machine[machines_count];
    for(int i = 0; i < machines_count; ++i){
      this -> machines[i].init(this);
    }
  }

  void printStatus() {
    clearSreen();
    for(int i = 0; i < types_count; ++i) {
      std::cout << "Type queue " << i << ": " << std::string(machines_count, '*') << std::endl;
    }
  }
};

int main(int argc, char **argv) {
  if(argv[1] == NULL){
    std::cout << "Program expect line.cnf as input\nExample:\n./a.out line.cnf\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  int N, M;
  infile >> N >> M;
  std::cout << "N = " << N << "\nM = " << M;
  Conveyor *conveyor = new Conveyor(N, M);
  conveyor -> printStatus();
  return 0;
}
