#pragma once
#include <core.task/ExtendedTask.h>
#include <simulation/ISimulationObject.h>
namespace nspace{

/**
 * \brief Simulation task. The task's run method is called as often as possible.  
 * 				
 *
 */
class SimulationTask : public virtual ISimulationObject, public virtual ExtendedTask{
  TYPED_OBJECT;
public:
  virtual void toString(std::ostream & o)const{
    ExtendedTask::toString(o);
  }

};


}