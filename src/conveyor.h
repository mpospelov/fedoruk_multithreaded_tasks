#ifndef CONVEYOR_H_INCLUDED_
#define CONVEYOR_H_INCLUDED_

#include "machine.h"
class Machine;

class Conveyor {
  int types_count;
  int machines_count;
  Machine *machines;
  void clearSreen();
public:
  Conveyor(int machines_count, int types_count);

  int getTypesCount();
  void printStatus();
};

#endif
