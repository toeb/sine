#pragma once

#include <Simulation/Core/ISimulationObject.h>
#include <vector>


namespace IBDS{

class IValue : public virtual ISimulationObject{
public:
  IValue(const std::string & name){setName(name);};
  virtual void set(const void * value)=0;
  virtual void get(void * value)=0;
};

}