#pragma once

#include <Simulation/Core/Simulation.h>
#include <Simulation/DynamicsAlgorithm.h>
#include <Simulation/Integration/SingleStepIntegrator.h>
namespace IBDS{
class CustomSimulation : public Simulation{
private:
  DynamicsAlgorithm dynamicsAlgorithm;
  SingleStepIntegrator * integrator;
public:
  void buildModel();
  void buildAlgorithms();
protected:
  bool initializeSimulation();
  void onSimulationObjectAdded(ISimulationObject * simObj);
};
}
