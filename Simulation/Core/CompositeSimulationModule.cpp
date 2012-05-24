#include "CompositeSimulationModule.h"

using namespace IBDS;

void CompositeSimulationModule::addSimulationModule(ISimulationModule * module){
  _modules.push_back(module);
}
void CompositeSimulationModule::removeSimulationModule(ISimulationModule * module){
  auto pos = std::find(_modules.begin(), _modules.end(), module);
  if(pos==_modules.end())return;
  _modules.erase(pos);
}
bool CompositeSimulationModule::addSimulationObject(ISimulationObject * object){
  bool result = false;
  std::for_each(_modules.begin(), _modules.end(), [&result,object](ISimulationModule* m){
    result |= m->add(object);
  });
  return result;
};
bool CompositeSimulationModule::removeSimulationObject(ISimulationObject * object){
  bool result = false;
  std::for_each(_modules.begin(), _modules.end(), [&result,object](ISimulationModule* m){
    result |= m->add(object);
  });
  return result;
}
bool CompositeSimulationModule::isCompatibleWith(ISimulationModule * module){
  bool result = true;
  std::for_each(_modules.begin(), _modules.end(), [&result,module](ISimulationModule* m){
    result &= m->isCompatibleWith(module);
  });
  return result;
}
  