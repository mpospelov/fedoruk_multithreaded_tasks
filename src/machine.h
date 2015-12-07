#ifndef MACHINE_H_INCLUDED_
#define MACHINE_H_INCLUDED_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "conveyor.h"
class Conveyor;

class Machine {
  Conveyor *Mconveyor;
  pthread_t *Mtid_p;
  pthread_mutex_t **Mlocks;
  int *Mtimes_config;
  int Mtypes_count;
  int Mid;
public:
  void init(Conveyor *conveyor, int id);
  void setTimeConfig(int *timeConfig);
  void launch();
  char* status();

  void *loop(void);
  static void *loop_helper(void *context);

};

#endif
