#ifndef CONVEYOR_H_INCLUDED_
#define CONVEYOR_H_INCLUDED_

#include "machine.h"
#include "printer.h"

class Machine;

class Conveyor {
  int Mtypes_count;
  int Mmachines_count;
  int Mworking_on_count;
  int Mfinished_device_count;
  Machine *Mmachines;
public:
  Printer *Mprinter;

  Conveyor(int machines_count, int types_count);

  int getTypesCount();
  void printStatus();
  void finish(int device);
  void parseTimeConfig(int **timeConfig);
  void launch();
  void workOn(int device);
};

#endif
