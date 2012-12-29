#pragma once
#include <functional>
#include <vector>

#include <config.h>

#include <simulation/ISimulationModule.h>
#include <simulation/composites/CompositeSimulationObject.h>

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
