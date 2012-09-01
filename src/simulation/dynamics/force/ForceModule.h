#pragma once
#include <simulation/core/ISimulationModule.h>
#include <simulation/force/Force.h>
#include <simulation/timing/Timeable.h>

namespace nspace{

class ForceAlgorithm: public ISimulationModule,public virtual Timeable{
  std::vector<Force *> _forces;
  std::vector<DynamicBody*> _forceAccumulators;
public:
  void applyForces(Real time);
  void resetForces();
  void setForces(Real time);

  ForceAlgorithm();

  void announce(ISimulationObject * object);
  void renounce(ISimulationObject * object);
};
}