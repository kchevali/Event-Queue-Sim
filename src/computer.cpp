#include <iostream>
#include "computer.h"

Computer::Computer(int cpuCapacity, int memCapacity, double serviceRate, double rho, int maxDepartureCount):
  cpuCapacity(cpuCapacity),
  memCapacity(memCapacity),
  userCapacity(0),
  arrivalRate1(rho * cpuCapacity * serviceRate), //CHECK u=serviceRate or (1/serviceRate)???
  arrivalRate2(0),
  serviceRate(serviceRate),
  rho(rho),
  maxDepartureCount(maxDepartureCount){

  init();
}

Computer::Computer(int cpuCapacity, int memCapacity, int userCapacity, double arrivalRate2, double serviceRate, double rho, int maxDepartureCount):
  cpuCapacity(cpuCapacity),
  memCapacity(memCapacity),
  userCapacity(userCapacity),
  arrivalRate1(rho * cpuCapacity * serviceRate), //CHECK u=serviceRate or (1/serviceRate)???
  arrivalRate2(arrivalRate2),
  serviceRate(serviceRate),
  rho(rho),
  maxDepartureCount(maxDepartureCount){

  init();
}

void Computer::init(){
  for(int i = 0; i < cpuCapacity; i++) cpuDepartures.push(0);

  //System event
  addArrivalEvent(true);

  //User event
  if(arrivalRate2 > 0)
    addArrivalEvent(false);
}

bool Computer::update(){
  Event* event = eventList.get();
  if(event == nullptr)return false;
  prev = clock, clock=event->time;

  event->isArrival() ? handleArrival(event->isSystem()) : handleDeparture(event->isSystem());

  delete event;
  return !isDone();
}

void Computer::handleArrival(bool isSystem){
  totalProgramTime += memSize*(clock-prev);
  arrivalAttempts++;
  if(memSize >= memCapacity || (!isSystem && memSize >= userCapacity)){
    blocks++;
  }else {
    memSize++;
    if (memSize==1)addDepartureEvent(isSystem);
  }
  addArrivalEvent(isSystem);
}

void Computer::handleDeparture(bool isSystem){
  totalProgramTime += memSize*(clock-prev);
  memSize--;
  departureCount++;
  if (memSize > 0) addDepartureEvent(isSystem);
}

void Computer::addArrivalEvent(bool isSystem){
  eventList.insert(clock + exp_rv(isSystem ? arrivalRate1 : arrivalRate2), ARR_BIT | (isSystem ? SYS_BIT : 0));
}

void Computer::addDepartureEvent(bool isSystem){
  double depTime = std::max(clock, cpuDepartures.top()) + exp_rv(serviceRate);
  cpuDepartures.pop();
  cpuDepartures.push(depTime);
  eventList.insert(depTime, (isSystem ? SYS_BIT : 0));
}

bool Computer::isDone(){
  return departureCount > maxDepartureCount;
}

double Computer::simAvgNumOfPrograms() const{
  return totalProgramTime/clock;
}

double Computer::theoryAvgNumOfPrograms() const{
  return rho/(1-rho);
}

double Computer::avgProgramTime() const{
  int arrivals = arrivalAttempts - blocks;
  return arrivals == 0 ? 0 : totalProgramTime / arrivals;
}

double Computer::blockingProb() const{
  return (double)blocks / (arrivalAttempts);
}

std::string Computer::getResult() const{
  return std::to_string(rho) + ", " +
    (userCapacity == 0 ? "" : (std::to_string(userCapacity) + ", ")) + 
    std::to_string(simAvgNumOfPrograms()) + ", " +
    std::to_string(avgProgramTime()) + ", " +
    std::to_string(blockingProb()) + ", " +
    std::to_string(departureCount) + ", " +
    std::to_string(blocks);
}



void Computer::results(){
  std::cout << "Current number of programs in system: " << memSize << std::endl;
  std::cout << "Average number of programs(simulation): " << simAvgNumOfPrograms() << std::endl;
  std::cout << "Expected number of programs (analysis): " << theoryAvgNumOfPrograms() << std::endl;
}