#pragma once

#include <core/NamedObject.h>
#include <core.initialization/Initializable.h>
namespace nspace{
  class Simulation;
  class ISimulationModule;

  /**
  * \brief Simulation object.
  * 				Base Object used with the Simulation and SimulationModule classes.  Only Simulation objects may be added to a SimulationModule / Simulation.
  * 				They are distributed accross the simulation tree.
  */
  class ISimulationObject : public virtual NamedObject, public virtual Initializable{
    TYPED_OBJECT(ISimulationObject);
  private:
    Simulation * _simulation;
    ISimulationModule * _parent;
  public:

    ISimulationObject();
    ISimulationObject(const std::string & name);
    virtual ~ISimulationObject(){}

    inline void setParent(ISimulationModule * parent){_parent=parent;}
    inline virtual void accepted(){};
    inline ISimulationModule * parent(){return _parent;}
    inline void setSimulation(Simulation * simulation){_simulation = simulation;}
    inline Simulation * simulation(){
      //if(!_simulation) ERROR("Cannot access simulation because it is null");
      return _simulation;
    }
  protected:
  };
}
