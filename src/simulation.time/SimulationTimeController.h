#pragma once

#include <simulation.time/SimulationTimeProvider.h>
#include <core.task/ScheduledTask.h>
#include <math.statistics/core.h>
#include <core/Reflection.h>
namespace nspace{

  class SimulationTimeController : 
    public virtual ISimulationObject,
    public virtual ScheduledTask, 
    public virtual PropertyChangingObject, 
    public virtual NamedObject{
      REFLECTABLE_OBJECT(SimulationTimeController);
  public:   
    DESCRIPTION(DesiredSpeed, "Controlls at which speed the simulation time is advanced (w.r.t real time)");
    DEFAULTVALUE(DesiredSpeed, Real(1.0));
    DISPLAYNAME(DesiredSpeed, "desired speed");
    PROPERTY(Real, DesiredSpeed){}
    
    PROPERTY(bool, Paused){}
    
    PUBLIC_FIELD_REFERENCE(AverageOverTime, MeanSpeed);
  
    READONLY_PROPERTY(Real, ActualSpeed);
    READONLY_PROPERTY(Real, RealTimeFactor);    
  
  private:   
    SimulationTimeProvider & _simulationTimeProvider;
  public:
    SimulationTimeController(SimulationTimeProvider & simulationTimeProvider, bool startPaused = false);

    void togglePause();

    inline SimulationTimeProvider & simulationTimeProvider() {
      return _simulationTimeProvider;
    }


    Real actualSpeedAverage();
    // overridden member of simulation task
    void timeout(Time dt,Time t);    
  };

}
