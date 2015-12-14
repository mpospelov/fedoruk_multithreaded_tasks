#include "machine.h"

Machine::Machine() {
  Mrunning = true;
}

void Machine::init(Conveyor *conveyor, int id) {
  Mconveyor = conveyor;
  Mid = id;
  Mtypes_count = Mconveyor -> getTypesCount();
  Mdevice_lock = new pthread_mutex_t;
  Mrunning_lock = new pthread_mutex_t;
  Mqueue_lock = new pthread_mutex_t;
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

void Machine::stop() {
  pthread_mutex_lock(Mrunning_lock);
  Mrunning = false;
  pthread_mutex_unlock(Mrunning_lock);
}

void *Machine::loop(void) {
  int fails_count = 0;
  struct timespec tw = {0,100000000};
  struct timespec tr;

  while((Mrunning && Mdevice_queue.empty()) || fails_count < 100) {
    pthread_mutex_lock(Mqueue_lock);
    if(!Mdevice_queue.empty()) {
      fails_count = 0;
      std::chrono::time_point<std::chrono::system_clock> start, end;
      int device = Mdevice_queue.front();
      start = std::chrono::system_clock::now();
      sleep(timeForHandle(device));
      end = std::chrono::system_clock::now();
      std::time_t start_time = std::chrono::system_clock::to_time_t(start);
      std::time_t end_time = std::chrono::system_clock::to_time_t(end);
      std::tm tm_start = *std::localtime(&start_time);
      std::tm tm_end = *std::localtime(&end_time);

      std::string log = "D:" + patch::to_string(device) +
                        "|M:" + patch::to_string(id()) + "   " +
                        patch::to_string(std::put_time(&tm_start, "%H:%M:%S")) + "   " +
                        patch::to_string(std::put_time(&tm_end, "%H:%M:%S"));

      Mdevice_queue.pop();
      if(isLast()){
        Mconveyor -> finishDevice(device);
      } else {
        Mnext_machine -> handle(device);
      }
      Mconveyor -> writeResult(log);
      Mconveyor -> printStatus();
    } else {
      fails_count++;
      nanosleep (&tw, &tr);
    }
    pthread_mutex_unlock(Mqueue_lock);
  }
  return NULL;
};

void Machine::wait() {
  pthread_join(*Mtid_p, NULL);
}

void *Machine::loop_helper(void *context){
  return ((Machine *)context) -> loop();
};

std::string Machine::status() {
  return "Q: " + patch::to_string(Mdevice_queue.size()) + " | " +
         "R: " + patch::to_string(!Mdevice_queue.empty()) +
         "(- seconds)";
}
