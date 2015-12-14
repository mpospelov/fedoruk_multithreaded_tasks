#ifndef MACHINE_H_INCLUDED_
#define MACHINE_H_INCLUDED_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include "patch.h"
#include "conveyor.h"

class Conveyor;

class Machine {
  Conveyor *Mconveyor;
  pthread_t *Mtid_p;
  pthread_mutex_t *Mdevice_lock;
  pthread_mutex_t *Mrunning_lock;
  pthread_mutex_t *Mqueue_lock;
  std::queue<int> Mdevice_queue;

  Machine *Mnext_machine;

  int *Mtimes_config;
  int Mtypes_count;
  int Mid;
  bool Mrunning;

  int timeForHandle(int device);
  bool isLast();
public:
  Machine();
  void init(Conveyor *conveyor, int id);
  void setTimeConfig(int *timeConfig);
  void setNextMachine(Machine *machine);
  void handle(int device);
  void launch();
  void stop();
  int id();
  std::string status();
  void wait();
  void *loop(void);
  static void *loop_helper(void *context);
};

#endif
