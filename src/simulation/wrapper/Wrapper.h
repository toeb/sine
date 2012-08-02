#pragma once
#include <simulation/core/ISimulationObject.h>

namespace mbslib{
class Wrapper : public ISimulationObject{
public:
  virtual ISimulationObject* wrap(ISimulationObject * object)=0;
};
}