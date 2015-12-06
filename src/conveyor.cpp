#include "conveyor.h"
#include <iostream>

void Conveyor::clearSreen(){
  std::cout << std::endl;
  system("clear");
}

Conveyor::Conveyor(int Nmachines_count, int Ntypes_count) {
  types_count = Ntypes_count;
  machines_count = Nmachines_count;
  machines = new Machine[machines_count];
  for(int i = 0; i < machines_count; ++i){
    machines[i].init(this);
  }
}

int Conveyor::getTypesCount(){
  return types_count;
}

void Conveyor::printStatus() {
  clearSreen();
  for(int i = 0; i < types_count; ++i) {
    std::cout << "Type queue " << i << ": " << std::string(machines_count, '*') << std::endl;
  }
}
