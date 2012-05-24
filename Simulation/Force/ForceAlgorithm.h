#pragma once
#include <Simulation/Core/ISimulationModule.h>
#include <Simulation/Force/Force.h>

namespace IBDS{

class ForceAlgorithm: public ISimulationModule{
  std::vector<Force *> _forces;
  std::vector<DynamicBody*> _forceAccumulators;
public:
  ForceAlgorithm();
  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);

  void applyForces(Real time);
  void resetForces();
  void setForces(Real time);

};
}