#pragma once
#include <Simulation/Core/ISimulationModule.h>
#include <Simulation/Force/Force.h>
#include <Simulation/Core/Timing/Timeable.h>

namespace IBDS{

class ForceAlgorithm: public ISimulationModule,public virtual Timeable{
  std::vector<Force *> _forces;
  std::vector<DynamicBody*> _forceAccumulators;
public:
  void applyForces(Real time);
  void resetForces();
  void setForces(Real time);

  ForceAlgorithm();

  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);
};
}