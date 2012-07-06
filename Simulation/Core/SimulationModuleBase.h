#pragma once
#include <Simulation/Core/ISimulationModule.h>
#include <vector>
#include <functional>
#include <algorithm>

namespace IBDS{

/**
 * \brief A base class for Simulationmodules which only use one type of ISimulationObjects.
 * 				everything is protected so only sublclasses can decide wether to make internal information public
 *
 * \author Tobi
 * \date 06.07.2012
 */
template<class T>
class SimulationModuleBase : public virtual ISimulationModule{
private:
  std::vector<T*> _objects;
public:

protected:
  //access to the objects
  void foreach(std::function<void(T*)> action);
  std::vector<T*> & objects();
    /**
   * \brief Accept object if this method returns true then the object is added.
   * 				
   * 				subclasses may override this
   * 				
   * \return true if it succeeds, false if it fails.
   */
  virtual bool acceptObject(T * object){return true;}

  //SimulationModule impl.
  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);

  //extension points
  virtual void onBeforeSimulationObjectAdd(ISimulationObject * object){}
  virtual void onBeforeSimulationObjectRemove(ISimulationObject * object){}
  virtual void onObjectAdded(T * object){ }
  virtual void onObjectRemoved(T * object){ }
};

// Implementation
template<class T>
bool SimulationModuleBase<T>::addSimulationObject(ISimulationObject * object){
  onBeforeSimulationObjectAdd(object);
  T* typedObject = dynamic_cast<T*>(object);
  if(!typedObject)return false;
  if(!acceptObject(typedObject))return false;
  _objects.push_back(typedObject);
  onObjectAdded(typedObject);
  return true;
}
template<class T>
bool  SimulationModuleBase<T>::removeSimulationObject(ISimulationObject * object){
  onBeforeSimulationObjectRemove(object);
  auto pos = std::find(_objects.begin(), _objects.end(), object);
  if(pos == _objects.end())return false;
  _objects.erase(pos);
  onObjectRemoved( dynamic_cast<T*>(object));
  return true;
}
template<class T>
void SimulationModuleBase<T>:: foreach(std::function<void(T*)> action){
      for_each(objects().begin(), objects().end(), action);
}
template<class T>
std::vector<T*> &  SimulationModuleBase<T>::objects(){
  return _objects;
}

}