#ifndef CONVEYOR_H_INCLUDED_
#define CONVEYOR_H_INCLUDED_

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "machine.h"
#include "printer.h"
#include "patch.h"

class Machine;
class Printer;

class Conveyor {
  int Mtypes_count;
  int Mmachines_count;
  int Mworking_on_count;
  int Mfinished_device_count;
  bool Mrunning;

  std::vector<std::string> Mresults;

  Machine *Mmachines;
public:
  Printer *Mprinter;

  Conveyor(int machines_count, int types_count);

  int getTypesCount();
  void printStatus();
  void finishDevice(int device);
  void parseTimeConfig(int **timeConfig);
  void launch();
  void workOn(int device);
  void writeResult(std::string log);
  void printResults();
  void printResultsToData();
  void finish();
  bool isRun();
};

#endif
