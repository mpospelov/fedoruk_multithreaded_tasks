#include "printer.h"

Printer::Printer() {
  Mcount_lock = new pthread_mutex_t;
  Mqueue_lock = new pthread_mutex_t;
  Mrunning = true;
  Mtid_p = new pthread_t;
  Mattr_p = new pthread_attr_t;
  pthread_attr_init(Mattr_p);
  pthread_attr_setscope(Mattr_p, PTHREAD_SCOPE_SYSTEM);
  pthread_attr_setdetachstate(Mattr_p, PTHREAD_CREATE_JOINABLE);

  if(pthread_create(Mtid_p, Mattr_p, &Printer::print_loop_helper, this)) {
    perror("pthread_create");
    sleep(1);
  }
}

void Printer::stop() {
  Mrunning = false;
}

void Printer::wait() {
  pthread_join(*Mtid_p, NULL);
}

void Printer::print(std::string value) {
  pthread_mutex_lock(Mcount_lock);
  Mqueue.push(value);
  pthread_mutex_unlock(Mcount_lock);
}

void *Printer::print_loop() {
  int fails_count = 0;
  while((Mrunning && Mqueue.empty()) || fails_count < 10){
    if(!Mqueue.empty()){
      fails_count = 0;
      std::cout.flush();
      system("clear");
      std::cout << std::endl << Mqueue.front() << std::endl;
      Mqueue.pop();
    } else {
      fails_count++;
    }
    sleep(1);
  }
  return NULL;
}

void *Printer::print_loop_helper(void *context) {
  return ((Printer *)(context)) -> print_loop();
}
