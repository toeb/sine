#include "CompositeSimulationObject.h"
#include <algorithm>
using namespace IBDS;
using namespace std;

CompositeSimulationObject::CompositeSimulationObject(){}
CompositeSimulationObject::~CompositeSimulationObject(){}

void CompositeSimulationObject::addSimulationObject(ISimulationObject* object){
  if(!object)return;
  _children.push_back(object);
}
bool CompositeSimulationObject::removeSimulationObject(ISimulationObject * object){
  if(!object)return false;
  auto it = find(_children.begin(),_children.end(),object);
  if(it == _children.end())return false;
  _children.erase(it);
  return true;
}

const std::vector<ISimulationObject*> & CompositeSimulationObject::children()const{
  return _children;
}
void CompositeSimulationObject::forEachChild(SimulationObjectAction action){
  for_each(_children.begin(),_children.end(),action);
}
void CompositeSimulationObject::forAllChildren(SimulationObjectAction action){
  for_each(_children.begin(),_children.end(),[action](ISimulationObject * child){
    action(child);
    auto composite = dynamic_cast<CompositeSimulationObject*>(child);
    if(composite){
      composite->forAllChildren(action);
    }
  });
}

bool CompositeSimulationObject::initializeObject(){
  bool result = true;
  forEachChild([&result](ISimulationObject * object){
    result &= object->initialize();
  });
  return result;
}
void CompositeSimulationObject::cleanupObject(){
  forEachChild([](ISimulationObject * object){
    object->cleanup();
  });
}

