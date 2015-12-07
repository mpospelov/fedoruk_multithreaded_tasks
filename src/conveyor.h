#ifndef CONVEYOR_H_INCLUDED_
#define CONVEYOR_H_INCLUDED_

#include "machine.h"
#include "printer.h"

class Machine;

class Conveyor {
  int Mtypes_count;
  int Mmachines_count;
  Machine *Mmachines;
  void clearSreen();
public:
  Printer *Mprinter;

  Conveyor(int machines_count, int types_count);

  int getTypesCount();
  void printStatus();
  void parseTimeConfig(int **timeConfig);
  void launch();
};

#endif
