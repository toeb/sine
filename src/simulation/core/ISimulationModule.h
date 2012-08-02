#pragma once
#include <simulation/core/ISimulationObject.h>

#include <vector>
#include <algorithm>
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
