#include "conveyor.h"
#include <iostream>

void Conveyor::clearSreen(){
  std::cout << std::endl;
  system("clear");
}

Conveyor::Conveyor(int machines_count, int types_count) {
  Mprinter = new Printer;
  Mtypes_count = types_count;
  Mmachines_count = machines_count;
  Mmachines = new Machine[Mmachines_count];
  for(int i = 0; i < machines_count; ++i){
    Mmachines[i].init(this, i);
  }
}

int Conveyor::getTypesCount() {
  return Mtypes_count;
}

void Conveyor::parseTimeConfig(int **config) {
  for(int i = 0; i < Mmachines_count; ++i) {
    Mmachines[i].setTimeConfig(config[i]);
  }
}

void Conveyor::launch() {
  for(int i = 0; i < Mmachines_count; ++i) {
    Mmachines[i].launch();
  }
  pthread_join(*(Mprinter -> Mtid_p), NULL);
}

void Conveyor::printStatus() {
  clearSreen();
  for(int i = 0; i < Mmachines_count; ++i) {
    std::cout << "Machine #" << i << ": " << Mmachines[i].status() << std::endl;
  }
}
