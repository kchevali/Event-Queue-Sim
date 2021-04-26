#include <fstream>
#include <iostream>
#include "computer.h"

int main()
{
  std::cout << "*********************************\n";
  std::cout << "Running Experiments\n";
  std::cout << "*********************************\n\n";

  std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
  std::cout.precision(1);

  std::ofstream f;
  f.open ("data/example.csv");
      
  //Experiment 1
  std::cout << "Experiment 1\n";
  std::cout << "---------------------------------\n";
  f << "Experiment 1\n";
  f << "Rho, Avg num of programs, Time spent by program, Blocking prob, departures, Block Count\n";
  for(double rho = 0.1; rho <= 1.0; rho += 0.1){
    std::cout <<  "   Rho: " << rho << ": ";
    int cpuCapacity = 2;
    int memCapacity = 4;
    double serviceRate = 3; //mu
    int maxDepartureCount = 2e5; // 200,000

    try{
      Computer comp(cpuCapacity, memCapacity, serviceRate, rho, maxDepartureCount);
      while (comp.update());
      f << comp.getResult() << "\n";
      std::cout << "DONE\n";
    }catch(...){
      std::cout << "ERR\n";
    }
  }

  //Experiment 2
  std::cout << "Experiment 2\n";
  std::cout << "---------------------------------\n";
  f << "\nExperiment 2\n";
  for( int userCapacity = 1; userCapacity <= 3; userCapacity += 2){
  f << "\nRho, User Capacity, Avg num of programs, Time spent by program, Blocking prob, departures, Block Count\n";
    for(double rho = 0.1; rho <= 1.0; rho += 0.1){
      std::cout <<  "   Rho: " << rho << " l: " << userCapacity << ": ";
      int cpuCapacity = 2;
      int memCapacity = 4;
      double arrivalRate2 = 4;
      double serviceRate = 3; //mu
      int maxDepartureCount = 2e5; // 200,000

      try{
        Computer comp(cpuCapacity, memCapacity, userCapacity, arrivalRate2, serviceRate, rho, maxDepartureCount);
        while (comp.update());
        f << comp.getResult() << "\n";
        std::cout << "DONE\n";
      }catch(...){
        std::cout << "ERR\n";
      }
    }
  }

  f.close();
  std::cout << "\nProgram terminated successfully\n";
}

