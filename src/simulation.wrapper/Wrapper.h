#pragma once
#include <simulation/ISimulationObject.h>

namespace nspace{
class Wrapper : public ISimulationObject{
public:
  virtual ISimulationObject* wrap(ISimulationObject * object)=0;
};
}