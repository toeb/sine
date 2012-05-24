#pragma once

#include <Simulation/Core/ISimulationModule.h>
#include <vector>

namespace IBDS{

/**
 * \brief Composite simulation module. 
 * 				combines multiple simulation modules into one
 *
 * \author Tobi
 * \date 20.05.2012
 */
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