#ifndef PRINTER_H_INCLUDED_
#define PRINTER_H_INCLUDED_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>

class Printer {
  pthread_attr_t *Mattr_p;
  pthread_mutex_t *Mqueue_lock;
  pthread_mutex_t *Mcount_lock;

  std::queue<std::string> Mqueue;
  void *print_loop();
  static void *print_loop_helper(void *context);
public:
  pthread_t *Mtid_p;

  Printer();

  void print(std::string value);
};

#endif
