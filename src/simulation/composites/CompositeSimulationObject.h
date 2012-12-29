#pragma once
#include <simulation/ISimulationObject.h>
#include <core/patterns/Composite.h>

#include <vector>
#include <functional>

namespace nspace{
  /**
  * \brief Composite simulation object.
  * 				The composite simulation object consists of multiple ISimulation objects
  *        these components are automatically handled by the simulation.
  *
  * \author Tobi
  * \date 15.07.2012
  */
  class CompositeSimulationObject : public virtual ISimulationObject, public virtual Composite<ISimulationObject>{
  public:
    CompositeSimulationObject();
    CompositeSimulationObject(const std::string & name);
    // calls the action on each successor
    void foreachSuccessor(std::function<void(ISimulationObject*)> action);
  };
}