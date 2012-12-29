#include "DefaultSimulationSetup.h"

#include <simulation.integration/implementations/RungeKutta4.h>

#include <simulation.time/SimulationTimeController.h>
#include <simulation.timing/TimingModule.h>
#include <simulation/Simulation.h>

using namespace nspace;
DefaultSimulationSetup::DefaultSimulationSetup():defaultSystem(&simulationTimeProvider){
}
bool DefaultSimulationSetup::initializeObject(){
  *simulation()<<simulationTimeProvider;

  // the integrator used is the explicit euler
  //*simulation() << new RungeKutta4(0.05);
  // the real time simulation module is used for advancing the simulation in real time
  *simulation() << new SimulationTimeController(simulationTimeProvider);
  // the timing module is used to measure how much time is needed by various objects
  *simulation() << timings;
  // the integrable system module connects the integrables, system functions and the integrator.
  //*simulation() << defaultSystem;

  return true;
}