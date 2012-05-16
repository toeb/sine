#pragma once

#include <Simulation/ISimulationModule.h>
#include <vector>

namespace IBDS{

class CompositeSimulationModule:public ISimulationModule{
private:
  std::vector<ISimulationModule*> _modules;
public:
  void addSimulationModule(ISimulationModule * module);
  void removeSimulationModule(ISimulationModule * module);

  bool addSimulationObject(ISimulationObject * object);
  bool removeSimulationObject(ISimulationObject * object);
  
  bool isCompatibleWith(ISimulationModule * module);
};
}