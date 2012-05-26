#pragma once
#include <Simulation/Core/ISimulationModule.h>
#include <vector>
#include <functional>
#include <algorithm>

namespace IBDS{
template<class T>
class SimulationModuleBase : public virtual ISimulationModule{
private:
  std::vector<T*> _objects;
public:
  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);

protected:
  virtual void onObjectAdded(T * object){ }
  virtual void onObjectRemoved(T * object){ }
  virtual bool acceptObject(T * object){return true;}

  void foreach(std::function<void(T*)> action);
  std::vector<T*> & objects();
};

template<class T>
bool SimulationModuleBase<T>::addSimulationObject(ISimulationObject * object){
  auto typedObject = dynamic_cast<T*>(object);
  if(!typedObject)return false;
  if(!acceptObject(typedObject))return false;
  _objects.push_back(typedObject);
  onObjectAdded(typedObject);
}
template<class T>
bool  SimulationModuleBase<T>::removeSimulationObject(ISimulationObject * object){
  auto pos = std::find(_objects.begin(), _objects.end(), object);
  if(pos == _objects.end())return false;
  _objects.erase(pos);
  onObjectRemoved( dynamic_cast<T*>(object));
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