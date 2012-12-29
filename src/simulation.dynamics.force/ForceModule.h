#pragma once
#include <simulation/ISimulationModule.h>
#include <simulation.dynamics.force/Force.h>
#include <simulation.timing/Timeable.h>

#include <vector>

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