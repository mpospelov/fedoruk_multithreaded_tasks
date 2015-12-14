#include "conveyor.h"

Conveyor::Conveyor(int machines_count, int types_count) {
  Mworking_on_count = 0;
  Mfinished_device_count = 0;
  Mprinter = new Printer;
  Mtypes_count = types_count;
  Mmachines_count = machines_count;
  Mmachines = new Machine[Mmachines_count];
  for(int i = 0; i < machines_count; ++i){
    Mmachines[i].init(this, i);
  }
  for(int i = 1; i < machines_count; ++i) {
    Mmachines[i - 1].setNextMachine(&Mmachines[i]);
  }
}

void Conveyor::writeResult(std::string log) {
  Mresults.push_back(log);
}

void Conveyor::printResultsToData() {
  std::ofstream data;
  data.open ("data.txt");
  for(std::vector<std::string>::iterator it = Mresults.begin(); it != Mresults.end(); ++it){
    data << *it << std::endl;
  }
}

void Conveyor::printResults() {
  std::cout.flush();
  std::cout << std::endl;
  for(std::vector<std::string>::iterator it = Mresults.begin(); it != Mresults.end(); ++it){
    std::cout.flush();
    std::cout << std::endl;
    std::cout << *it;
  }
  std::cout.flush();
  std::cout << std::endl;
}

void Conveyor::workOn(int device) {
  Mworking_on_count ++;
  Mmachines[0].handle(device);
}

void Conveyor::finishDevice(int device) {
  Mworking_on_count --;
  Mfinished_device_count ++;
}

int Conveyor::getTypesCount() {
  return Mtypes_count;
}

void Conveyor::parseTimeConfig(int **config) {
  for(int i = 0; i < Mmachines_count; ++i) {
    Mmachines[i].setTimeConfig(config[i]);
  }
}

void Conveyor::launch() {
  for(int i = 0; i < Mmachines_count; ++i) {
    Mmachines[i].launch();
  }
}

void Conveyor::printStatus() {
  std::string status;
  for(int i = 0; i < Mmachines_count; ++i) {
    status += "Machine #" + patch::to_string(Mmachines[i].id()) + ": " + Mmachines[i].status() + "\n";
  }
  status += ("\nOn work: " + patch::to_string(Mworking_on_count) +
             "\nFinished Devices: " + patch::to_string(Mfinished_device_count) + "\n");
  Mprinter -> print(status);
}

void Conveyor::finish() {
  for (int i = 0; i < Mmachines_count; ++i) {
    Mmachines[i].stop();
  }
  Mprinter -> stop();
  Mmachines[Mmachines_count - 1].wait();
  Mprinter -> wait();
}
