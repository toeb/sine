#pragma once

#include <common/Config.h>
#include <simulation/core/ISimulationModule.h>
#include <simulation/core/composites/CompositeSimulationObject.h>

#include <functional>
#include <vector>

namespace nspace{
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

  void addModule(ISimulationModule * module);
  void removeModule(ISimulationModule * module);
};
}
