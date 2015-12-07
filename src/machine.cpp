#include "machine.h"

void Machine::init(Conveyor *conveyor, int id) {
  Mconveyor = conveyor;
  Mid = id;
  Mtypes_count = Mconveyor -> getTypesCount();
  Mlocks = new pthread_mutex_t*[Mtypes_count];

  for(int i = 0; i < Mtypes_count; ++i) {
    Mlocks[i] = new pthread_mutex_t;
    pthread_mutex_init(Mlocks[i], NULL);
  }
}

void Machine::setTimeConfig(int *timeConfig) {
  Mtimes_config = new int[Mtypes_count];

  memcpy(Mtimes_config, timeConfig, sizeof(int) * Mtypes_count);
}

void Machine::launch() {
  Mtid_p = new pthread_t;
  pthread_attr_t *attr_p = new pthread_attr_t;
  pthread_attr_init(attr_p);
  pthread_attr_setscope(attr_p, PTHREAD_SCOPE_SYSTEM);
  pthread_attr_setdetachstate(attr_p, PTHREAD_CREATE_JOINABLE);

  if(pthread_create(Mtid_p, attr_p, &Machine::loop_helper, this)) {
    perror("pthread_create");
  }
}

void *Machine::loop(void) {
  Mconveyor -> Mprinter -> print("Machine #" + std::to_string(Mid) + " launched!\n");
  while(1) {
    Mconveyor -> Mprinter -> print("Hi from Machine #" + std::to_string(Mid) + "\n");
    sleep(1);
  }
  return NULL;
};

void *Machine::loop_helper(void *context){
  return ((Machine *)context) -> loop();
};

char* Machine::status() {
  char *result;

  return "";
}
