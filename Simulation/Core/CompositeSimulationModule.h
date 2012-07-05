#pragma once
#include <Simulation/Core/CompositeSimulationObject.h>
#include <Simulation/Core/ISimulationModule.h>

#include <functional>
#include <vector>

namespace IBDS{
/**
 * \brief Composite simulation module. 
 * 				combines multiple simulation modules into one
 *
 */
class CompositeSimulationModule:public virtual ISimulationModule, public virtual CompositeSimulationObject{
private:
  std::vector<ISimulationModule*> _modules;
public:
  const std::vector<ISimulationModule*> & modules()const{return _modules;}

  void foreachModule(std::function<void (ISimulationModule*)> f);

  void addChild(ISimulationModule * module);
  void removeChild(ISimulationModule * module);
};
}