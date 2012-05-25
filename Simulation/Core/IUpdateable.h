#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
namespace IBDS{
class IUpdatable:public virtual ISimulationObject{
public:
  virtual void update(Real t, Real h)=0;
};
}