#include "CompositeSimulationModule.h"
#include <algorithm>
using namespace nspace;
void CompositeSimulationModule::foreachModule(std::function<void (ISimulationModule*)> f){
  for_each(_modules.begin(), _modules.end(), f);
}
void CompositeSimulationModule::addModule(ISimulationModule * module){
  addComponent(module);
  _modules.push_back(module);
}
void CompositeSimulationModule::removeModule(ISimulationModule * module){
  removeComponent(module);
  auto pos = std::remove(_modules.begin(), _modules.end(), module);
}  