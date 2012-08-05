#pragma once
#include <simulation/core/ISimulationObject.h>

namespace nspace{
/**
 * \brief 
 *
 */
  
class ISimulationModule:public virtual ISimulationObject{
public:  
  virtual void announce(ISimulationObject * object)=0;  
  virtual void renounce(ISimulationObject * object)=0;
 

};

}
