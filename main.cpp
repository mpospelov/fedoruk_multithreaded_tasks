#include <fstream>
#include <iostream>

class Machine {
public:
  Machine(Conveyor *conveyor) {

  }
};

class Conveyor {
  int types_count;
  Machine *machines;
public:
  Conveyor(int machines_count, int types_count) {
    this -> types_count = types_count;
    machines = (Machine)malloc(machines_count * sizeof(Machine));
    for(int i = 0; i < machines_count; ++i){
      machines[i] = new Machine(this);
    }
  }
};

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
  return 0;
}
