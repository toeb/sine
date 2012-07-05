#pragma once
#include <Simulation/Core/ISimulationObject.h>

namespace IBDS{
class Camera : virtual public ISimulationObject{
public:
  virtual void camera()=0;
};
}