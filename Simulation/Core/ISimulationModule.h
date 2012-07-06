#pragma once
#include <Simulation/Core/ISimulationObject.h>
#include <Math/MathDefs.h>
#include <vector>
#include <algorithm>
namespace IBDS{

/**
 * \brief Simulation module.  Used to respond to Simulationobjects added to the simulation
 * 				makes sure that all children are initialized when it itself is initialized
 * 				
 * 				Algorithms implement this
 *
 */
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

  /**
  /* Subclasses check to see if the need the object
   * \brief Adds a simulation object.  return true if added
   * 				
   *
   * \return true if it succeeds, false if it fails.
   */
  virtual bool addSimulationObject(ISimulationObject * object){return false;};
  virtual bool removeSimulationObject(ISimulationObject * object){return false;}
};

}