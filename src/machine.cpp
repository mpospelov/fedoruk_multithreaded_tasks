#include "machine.h"

void Machine::init(Conveyor *conveyor) {
  this -> conveyor = conveyor;
  int locks_count = conveyor -> getTypesCount();
  locks = new pthread_mutex_t*[locks_count];

  for(int i = 0; i < locks_count; ++i) {
    locks[i] = new pthread_mutex_t;
    pthread_mutex_init(locks[i], NULL);
  }
}
