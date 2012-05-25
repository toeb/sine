#pragma once


#include <Simulation/Core/SimulationModuleBase.h>
#include <Simulation/Core/IUpdateable.h>
namespace IBDS{
class UpdatablesModule : public virtual SimulationModuleBase<IUpdatable>{
public:
  void update(Real t, Real h);
};
}