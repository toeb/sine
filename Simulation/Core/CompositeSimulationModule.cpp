#include "CompositeSimulationModule.h"

using namespace IBDS;
void CompositeSimulationModule::foreachModule(std::function<void (ISimulationModule*)> f){
  for_each(_modules.begin(), _modules.end(), f);
}
void CompositeSimulationModule::addChild(ISimulationModule * module){
  CompositeSimulationObject::addChild(module);
  _modules.push_back(module);
}
void CompositeSimulationModule::removeChild(ISimulationModule * module){
  CompositeSimulationObject::removeChild(module);
  auto pos = std::find(_modules.begin(), _modules.end(), module);
  if(pos==_modules.end())return;
  _modules.erase(pos);
}  