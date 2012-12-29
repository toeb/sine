#include "CompositeSimulationObject.h"
#include <algorithm>

using namespace nspace;
using namespace std;

CompositeSimulationObject::CompositeSimulationObject(){}
CompositeSimulationObject::CompositeSimulationObject(const std::string & name)
  :ISimulationObject(name){}

void CompositeSimulationObject::foreachSuccessor(std::function<void (ISimulationObject*)> action){
  foreachComponent([action](ISimulationObject * component){
    action(component);
    auto composite = dynamic_cast<CompositeSimulationObject*>(component);
    if(composite){
      composite->foreachSuccessor(action);
    }
  });
}
/*

bool CompositeSimulationObject::isEmpty()const{
return _components.empty();
}
const std::vector<ISimulationObject*> & CompositeSimulationObject::components()const{
return _components;
}
void CompositeSimulationObject::foreachComponent(std::function<void(ISimulationObject*)> action){
for_each(_components.begin(), _components.end(), action);
}
void CompositeSimulationObject::foreachComponent(std::function<void(ISimulationObject*)> action) const{
for_each(_components.begin(), _components.end(), action);
}
bool CompositeSimulationObject::addComponent(ISimulationObject* component){
_components.push_back(component);
return true;
}
void CompositeSimulationObject::removeComponent(ISimulationObject* component){
std::remove(_components.begin(), _components.end(), component);
}

*/