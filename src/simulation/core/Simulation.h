#pragma once

#include <simulation/core/ISimulationModule.h>

#include <functional>
#include <set>
#include <queue>



namespace nspace{

class Simulation : public ISimulationObject{
  TYPED_OBJECT;
private:  
  ///< true if currently processing objects
  bool _processing;
  std::queue<ISimulationObject*> _queue;
  ///< The simulation objects
  std::set<ISimulationObject*> _objects;
  ///< The simulation modules
  std::set<ISimulationModule*> _modules;  
public:
  void toString(std::ostream & out)const;
  Simulation();
  
  /**
   * \brief Adds simulationObject / simulation module to the simulation.
   * 				
   * \return true if it succeeds, false if it fails.
   */
  void add(ISimulationObject * simulationObject);

  /**
   * \brief Removes the given simulationObject from the simulation.
   * 				
   * 				the effects might be unintended consequences depending on the modules added
   *
   * \return true if it succeeds, false if it fails.
   */
  void remove(ISimulationObject * simulationObject);

  /**
   * \brief adds a object to the simulation
   */
  Simulation & operator <<(ISimulationObject * object);
   /**
   * \brief adds a object to the simulation
   */
  Simulation & operator <<(ISimulationObject & object);
  /**
   * \brief remove the simulationobject from the simulation
   */
  Simulation & operator >>(ISimulationObject * object);
  /**
   * \brief remove the simulationobject from the simulation
   */
  Simulation & operator >>(ISimulationObject & object);

  /**
   * \brief indexer operator returns the simulation object with the name.
   *
   * \param name The name.
   *
   * \return The indexed value.
   */
  ISimulationObject * operator[](const std::string & name);
  ISimulationObject * find(const std::string & name);

  void foreachModule(std::function<void(ISimulationModule*)> f);
  void foreachObject(std::function<void(ISimulationObject*)> f);
  void foreachObjectConst(std::function<void(ISimulationObject*)> f)const;

protected:
  //extension points of ISimulationObject
  bool initializeObject();
  //new extension point
	virtual bool initializeSimulation(){return true;};
  /**
   * \brief may be overridden.  gets called when a simulation object was added
   *
   * \author Tobi
   * \date 12.05.2012
   *
   * \param [in,out] object If non-null, the object.
   */
  virtual void onSimulationObjectAdded(ISimulationObject * object){};
  virtual void onSimulationObjectRemoved(ISimulationObject * object){};

private:
  bool processComposite(ISimulationObject * composite);
  bool processModule(ISimulationObject *  module);
  bool processQueuedObjects();
  bool processObject(ISimulationObject * object);
  bool removeSimulationModule(ISimulationModule * module);
};


}