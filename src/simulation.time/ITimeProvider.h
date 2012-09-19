#pragma once

#include <simulation/ISimulationObject.h>
#include <common/Time.h>
namespace nspace{

class ITimeProvider : public virtual ISimulationObject{
public:
  virtual Time time() const=0;
};

}