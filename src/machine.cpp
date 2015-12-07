#include "machine.h"

void Machine::init(Conveyor *conveyor, int id) {
  Mconveyor = conveyor;
  Mid = id;
  Mtypes_count = Mconveyor -> getTypesCount();
  Mdevice_lock = new pthread_mutex_t;
  pthread_mutex_init(Mdevice_lock, NULL);
}

void Machine::setTimeConfig(int *timeConfig) {
  Mtimes_config = new int[Mtypes_count];

  memcpy(Mtimes_config, timeConfig, sizeof(int) * Mtypes_count);
}

void Machine::setNextMachine(Machine *machine) {
  Mnext_machine = machine;
}

void Machine::handle(int device) {
  pthread_mutex_lock(Mdevice_lock);
  Mdevice_queue.push(device);
  pthread_mutex_unlock(Mdevice_lock);
}

int Machine::timeForHandle(int device) {
  return Mtimes_config[device];
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

bool Machine::isLast() {
  return Mnext_machine == NULL;
}

int Machine::id(){
  return Mid;
}

void *Machine::loop(void) {
  while(1) {
    if(!Mdevice_queue.empty()) {
      int device = Mdevice_queue.front();
      sleep(timeForHandle(device));
      Mdevice_queue.pop();
      if(isLast()){
        Mconveyor -> finish(device);
      } else {
        Mnext_machine -> handle(device);
        Mconveyor -> printStatus();
      }
    } else {
      sleep(1);
    }
  }
  return NULL;
};

void *Machine::loop_helper(void *context){
  return ((Machine *)context) -> loop();
};

std::string Machine::status() {
  return "Q: " + patch::to_string(Mdevice_queue.size()) + " | "
         "R: " + patch::to_string(!Mdevice_queue.empty());
}
