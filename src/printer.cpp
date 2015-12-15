#include "printer.h"

Printer::Printer(Conveyor *conveyor) {
  Mconveyor = conveyor;
  Mqueue_lock = new pthread_mutex_t;
  Mpush_in_queue = new pthread_cond_t;
  pthread_cond_init(Mpush_in_queue, NULL);
  pthread_mutex_init(Mqueue_lock, NULL);

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

void Printer::wait() {
  pthread_join(*Mtid_p, NULL);
}

void Printer::print(std::string value) {
  pthread_mutex_lock(Mqueue_lock);
  Mqueue.push(value);
  pthread_mutex_unlock(Mqueue_lock);
  pthread_cond_signal(Mpush_in_queue);
}

void *Printer::print_loop() {
  pthread_mutex_lock(Mqueue_lock);
  while(1){
    timespec timeout;
    timeout.tv_sec = time(NULL) + 1;
    timeout.tv_nsec = 0;
    pthread_cond_timedwait(Mpush_in_queue, Mqueue_lock, &timeout);
    if(!Mconveyor -> isRun() && Mqueue.empty()) break;
    if(Mqueue.empty()) continue;
    std::cout.flush();
    system("clear");
    std::cout << std::endl << Mqueue.front() << std::endl;
    Mqueue.pop();
  }
  pthread_mutex_unlock(Mqueue_lock);
  std::cout << "Done!\n";
  return NULL;
}

void *Printer::print_loop_helper(void *context) {
  return ((Printer *)(context)) -> print_loop();
}
