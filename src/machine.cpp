#include "machine.h"

void Machine::init(Conveyor *conveyor) {
  this -> conveyor = conveyor;
  for(int i = 0; i < conveyor -> getTypesCount(); ++i) {
    // pthread_mutex_init(locks[i], NULL);
  }
}
