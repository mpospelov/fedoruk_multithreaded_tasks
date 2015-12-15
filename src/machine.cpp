#include "machine.h"

const int Machine::EXIT_SIGNAL = -1;

Machine::Machine() {
  Mrunning = true;
  Mdone = false;
}

void Machine::init(Conveyor *conveyor, int id) {
  Mconveyor = conveyor;
  Mid = id;
  Mtypes_count = Mconveyor -> getTypesCount();
  Mqueue_lock = new pthread_mutex_t;
  Mpush_in_queue = new pthread_cond_t;

  pthread_cond_init(Mpush_in_queue, NULL);
  pthread_mutex_init(Mqueue_lock, NULL);
}

void Machine::setTimeConfig(int *timeConfig) {
  Mtimes_config = new int[Mtypes_count];

  memcpy(Mtimes_config, timeConfig, sizeof(int) * Mtypes_count);
}

void Machine::setNextMachine(Machine *machine) {
  Mnext_machine = machine;
  machine -> setPreviousMachine(this);
}

void Machine::setPreviousMachine(Machine *machine) {
  Mprevious_machine = machine;
}

void Machine::handle(int device) {
  // pthread_mutex_lock(Mqueue_lock);
  Mdevice_queue.push(device);
  // pthread_mutex_unlock(Mqueue_lock);
  pthread_cond_signal(Mpush_in_queue);
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

bool Machine::isDone() {
  return Mdone;
}

bool Machine::isLast() {
  return Mnext_machine == NULL;
}

bool Machine::isFirst() {
  return Mprevious_machine == NULL;
}

int Machine::id(){
  return Mid;
}

void Machine::stop() {
  Mrunning = false;
}

void *Machine::loop(void) {
  pthread_mutex_lock(Mqueue_lock);
  while(1) {
    timespec timeout;
    timeout.tv_sec = time(NULL);
    timeout.tv_nsec = 100000;
    pthread_cond_timedwait(Mpush_in_queue, Mqueue_lock, &timeout);
    if((isFirst() || Mprevious_machine -> isDone()) && !Mrunning && Mdevice_queue.empty()) break;
    if(Mdevice_queue.empty()) continue;

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
  }
  Mdone = true;
  pthread_mutex_unlock(Mqueue_lock);
  return NULL;
};

void Machine::wait() {
  pthread_join(*Mtid_p, NULL);
}

void *Machine::loop_helper(void *context){
  return ((Machine *)context) -> loop();
};

std::string Machine::status() {
  std::string result = "Q: " + patch::to_string(Mdevice_queue.size()) + " | " +
                       "R: " + patch::to_string(!Mdevice_queue.empty());
  if(!Mdevice_queue.empty()) {
    result += "(" + patch::to_string(timeForHandle(Mdevice_queue.front())) + " - seconds)";
  }
  return result;
}
