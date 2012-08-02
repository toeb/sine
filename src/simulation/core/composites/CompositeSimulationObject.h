#pragma once
#include <simulation/core/ISimulationObject.h>
#include <common/patterns/Composite.h>

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
class CompositeSimulationObject : public virtual ISimulationObject, public virtual IComposite<ISimulationObject>{
private:
  std::vector<ISimulationObject * > _components;
public:
  CompositeSimulationObject();
  CompositeSimulationObject(const std::string & name);
  // calls the action on each successor
  void foreachSuccessor(std::function<void(ISimulationObject*)> action);

  //members of IComposite
  bool isEmpty()const;  
  const std::vector<ISimulationObject*> & components()const;
  void foreachComponent(std::function<void(ISimulationObject*)> action);
  void foreachComponent(std::function<void(ISimulationObject*)> action) const;
  bool addComponent(ISimulationObject* component);
  void removeComponent(ISimulationObject* component);
};



}