#ifndef COMPUTER_H
#define COMPUTER_H

#include <queue>
#include <string>
#include "event.h"
#include "rv.h"


class Computer{
  public:
    Computer(int cpuCapacity, int memCapacity, double serviceRate, double rho, int maxDepartureCount);
    Computer(int cpuCapacity, int memCapacity, int userCapacity, double arrivalRate2, double serviceRate, double rho, int maxDepartureCount);

    // Computer(int cpuCapacity, int memCapacity, double arrivalRate, double serviceRate, int maxDepartureCount);
    virtual ~Computer(){}
    void init();

    bool update();
    void results();
    void handleArrival(bool isSystem);
    void handleDeparture(bool isSystem);
    void addArrivalEvent(bool isSystem);
    void addDepartureEvent(bool isSystem);
    bool isDone();

    //Calculations
    double simAvgNumOfPrograms() const; //simulation's average number of programs
    double theoryAvgNumOfPrograms() const; // theortical average number programs
    double avgProgramTime() const; // average time each program is in the system
    double blockingProb() const; // blocking probability vs rho
    std::string getResult() const;

  private:
    EventList eventList;
    std::priority_queue<double> cpuDepartures;

    // Constants
    int cpuCapacity;
    int memCapacity;
    int userCapacity;
    double arrivalRate1;
    double arrivalRate2;
    double serviceRate;
    double rho;
    int maxDepartureCount;

    // System
    double clock = 0.0;
    double prev = 0.0;
    int memSize = 0;
    double totalProgramTime = 0;
    int blocks=0;
    int arrivalAttempts=0;

    int departureCount = 0;
};

#endif