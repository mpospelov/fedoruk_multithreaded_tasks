#ifndef MACHINE_H_INCLUDED_
#define MACHINE_H_INCLUDED_

#include <pthread.h>
#include "conveyor.h"
class Conveyor;

class Machine {
  Conveyor *conveyor;
  pthread_mutex_t **locks;
public:
  void init(Conveyor *conveyor);
};

#endif
