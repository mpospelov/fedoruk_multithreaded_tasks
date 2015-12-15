#ifndef PRINTER_H_INCLUDED_
#define PRINTER_H_INCLUDED_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>
#include "conveyor.h"
#include "patch.h"

class Conveyor;

class Printer {
  pthread_attr_t *Mattr_p;
  pthread_mutex_t *Mqueue_lock;
  pthread_cond_t *Mpush_in_queue;
  Conveyor *Mconveyor;
  std::queue<std::string> Mqueue;
  void *print_loop();
  static void *print_loop_helper(void *context);
  static const std::string EXIT_SIGNAL;
public:
  pthread_t *Mtid_p;

  Printer(Conveyor *conveyor);
  void print(std::string value);
  void wait();
};

#endif
