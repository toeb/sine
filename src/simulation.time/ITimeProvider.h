#pragma once

#include <core/Time.h>

#include <simulation/ISimulationObject.h>
namespace nspace{
  class ITimeProvider : public virtual ISimulationObject{
  public:
    virtual Time time() const=0;
  };
}