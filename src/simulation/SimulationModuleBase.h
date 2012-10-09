#pragma once
#include <simulation/ISimulationModule.h>

#include <vector>
#include <functional>
#include <algorithm>

namespace nspace{

/**
 * \brief A base class for Simulationmodules which only use one type of ISimulationObjects.
 * 				everything is protected so only sublclasses can decide wether to make internal information public
 *
 * 
 */
template<class T>
class SimulationModuleBase : public virtual ISimulationModule{
  TYPED_OBJECT(SimulationModuleBase)
private:
  std::vector<T*> _objects;
public:
protected:
  //access to the objects
  void foreachObject(std::function<void(T*)> action);
  void foreachObject(std::function<void(T*)> action)const;
  std::vector<T*> & objects();
	const std::vector<T*> & objects()const;

    /**
   * \brief Accept object if this method returns true then the object is added.
   * 				
   * 				subclasses may override this
   * 				
   * \return true if it succeeds, false if it fails.
   */
  virtual bool acceptObject(T * object){return true;}

  //SimulationModule impl.
  void announce(ISimulationObject * object);
  void renounce(ISimulationObject * object);

  //extension points
 
  virtual void onPotentialSimulationObjectAdd(ISimulationObject * object){}
  virtual void onPotentialSimulationObjectRemove(ISimulationObject * object){}
	virtual void onBeforeObjectAdded(T * object){}
  virtual void onObjectAdded(T * object){ }
	virtual void onBeforeObjectRemoved(T* object){}
  virtual void onObjectRemoved(T * object){ }
  virtual void onObjectRejected(ISimulationObject * object){ }
  virtual void onSimulationSet(){};
};

// Implementation
template<class T>
void SimulationModuleBase<T>::announce(ISimulationObject * object){
  onPotentialSimulationObjectAdd(object);
  T* typedObject = dynamic_cast<T*>(object);
  if(!typedObject){
    onObjectRejected(object);
    return;
  }
  if(!acceptObject(typedObject))return ;
	onBeforeObjectAdded(typedObject);
  _objects.push_back(typedObject);
  onObjectAdded(typedObject);
}
template<class T>
void SimulationModuleBase<T>::renounce(ISimulationObject * object){
  onPotentialSimulationObjectRemove(object);
  auto pos = std::find(_objects.begin(), _objects.end(), object);
  if(pos == _objects.end())return;
	onBeforeObjectRemoved(dynamic_cast<T*>(object));
  _objects.erase(pos);
  onObjectRemoved( dynamic_cast<T*>(object));
}
template<class T>
void SimulationModuleBase<T>:: foreachObject(std::function<void(T*)> action){
      for_each(objects().begin(), objects().end(), action);
}

template<class T>
void SimulationModuleBase<T>:: foreachObject(std::function<void (T*)> action)const {
	for(auto it = objects().begin(); it != objects().end(); it++){
		action(*it);
	}
}
template<class T>
std::vector<T*> &  SimulationModuleBase<T>::objects(){
  return _objects;
}
template<class T>
const std::vector<T*> &  SimulationModuleBase<T>::objects()const{
  return _objects;
}

}