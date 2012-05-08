#pragma once
#include <Simulation/ISimulationObject.h>
namespace IBDS{
class IRenderer:public ISimulationObject{
public:
  virtual void render(){};
};
}
