#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
#include <vector>
#include <algorithm>
namespace IBDS{


class ISimulationModule:public virtual ISimulationObject{
public:
  bool add(ISimulationObject * object){
    if(!addSimulationObject(object))return false;
    if(isInitialized()){
      if(!object->initialize()){
         return false;
      }
    }
  }
  bool remove(ISimulationObject * object){
   return removeSimulationObject(object);
  }
  virtual bool isCompatibleWith(ISimulationModule * module){return true;}
protected:

  virtual bool addSimulationObject(ISimulationObject * object){return false;};
  virtual bool removeSimulationObject(ISimulationObject * object){return false;}
};

}