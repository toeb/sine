#pragma once
#include <Simulation/Core/ISimulationObject.h>

namespace IBDS{

class IAction : public virtual ISimulationObject{
public:
  IAction(const std::string & name){setName(name);}
  virtual void execute()=0;
};

}




