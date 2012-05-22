#ifndef __CustomSimulation_h__
#define __CustomSimulation_h__

#include <Simulation/Simulation.h>
#include <Simulation/DynamicsAlgorithm.h>
#include <Simulation/Integrators/SingleStepIntegrator.h>
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
#endif