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

  int **timeConfig = new int*[N];
  for(int i = 0; i < N; ++i) {
    timeConfig[i] = new int[M];
    for(int j = 0; j < M; ++j) {
      infile >> timeConfig[i][j];
      std::cout << timeConfig[i][j] << ",";
    }
    std::cout << std::endl;
  }

  conveyor -> parseTimeConfig(timeConfig);
  conveyor -> printStatus();
  return 0;
}
