#include "SimulationRunner.h"
#include <iostream>

using namespace std;
using namespace nspace;

bool SimulationRunner::initializeObject(){
  if(!simulation())return false;
  if(!simulation()->isInitialized()){
    if(!simulation()->initialize())return false;
  }
  if(!initializeRunner())return false;
  return true;
}
SimulationRunner::SimulationRunner(){
}
SimulationRunner::~SimulationRunner(){
}
void SimulationRunner::stop(){
  stopRunner();
}
int SimulationRunner::run(){
  if(!simulation()){
    cerr << "SimulationRunner: Simulation is not set" << endl;
    return 1;
  }
  if(!simulation()->initialize()){
    cerr << "SimulationRunner: Simulation could not be initialized" << endl;
    return 1;
  }

  return executeRunner();
}

void SimulationRunner::executeTasks(){
  //this could be extended to use a scheduler and multithreading
  foreachObject([](SimulationTask * task){
    task->run();
  });
}