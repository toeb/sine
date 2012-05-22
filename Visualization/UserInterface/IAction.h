#pragma once

#include <Simulation/ISimulationObject.h>

#include <Visualization/UserInterface/IComponent.h>

namespace IBDS{

class IAction : public virtual ISimulationObject, public virtual IComponent{
public:
  IAction(const std::string & name){setName(name);}
  virtual void execute()=0;

};

}




