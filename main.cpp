#include <fstream>
#include <iostream>
#include "src/machine.h"
#include "src/conveyor.h"

int main(int argc, char **argv) {
  if(argv[1] == NULL){
    std::cout << "Program expect line.cnf as input\nExample:\n./a.out line.cnf\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  int N, M;
  infile >> N >> M;
  std::cout << "N = " << N << "\nM = " << M;
  Conveyor *conveyor = new Conveyor(N, M);
  conveyor -> printStatus();
  return 0;
}
