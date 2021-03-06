#include <fstream>
#include <iostream>
#include <pthread.h>
#include "src/machine.h"
#include "src/conveyor.h"

int main(int argc, char **argv) {
  if(argv[1] == NULL){
    std::cout.flush();
    std::cout << "Program expect line.cnf as input\nExample:\n./a.out line.cnf\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  int N, M;
  infile >> N >> M;
  std::cout.flush();
  std::cout << "N = " << N << "\nM = " << M << std::endl;

  Conveyor *conveyor = new Conveyor(N, M);

  int **timeConfig = new int*[N];
  for(int i = 0; i < N; ++i) {
    timeConfig[i] = new int[M];
    for(int j = 0; j < M; ++j) {
      infile >> timeConfig[i][j];
    }
  }

  conveyor -> parseTimeConfig(timeConfig);
  conveyor -> printStatus();
  conveyor -> launch();
  int passed_device;
  while(std::cin >> passed_device) {
    conveyor -> workOn(passed_device);
  }
  conveyor -> finish();
  conveyor -> printResults();
  conveyor -> printResultsToData();
  system("gnuplot -geometry 1200x700  -persist gnu.txt");
  return 0;
}
