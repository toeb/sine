#pragma once
#include <Simulation/ISimulationAlgorithm.h>
#include <Simulation/SimulationObjects/Force.h>

namespace IBDS{

class ForceAlgorithm: public ISimulationAlgorithm{
  std::vector<Force *> _forces;
  std::vector<Body*> _forceAccumulators;
public:
  ForceAlgorithm();
  bool addSimulationObject(ISimulationObject * object);
  void precomputeStep();
  void preIntegrationStep(Real time, Real h);
  void reset();

};
}