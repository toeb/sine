#pragma once
#include <simulation.time/SimulationTimeProvider.h>
#include <simulation.time/PeriodicTask.h>

#include <math.statistics/core.h>

#include <queue>
namespace nspace{
  
class SimulationTimeController : public virtual PeriodicTask{
private:   
    ///< The desired speed this module is advancing the simulation time at (in multiples of real time)
    Real _desiredSpeed;
    ///< The actual speed this simulation has reached
    Real _actualSpeed;
    AverageOverTime _meanSpeed;

    ///< The real time factor: this quotient is between 0+ and 1.  1 describes the controller running  at real time
    Real _realTimeFactor;

    ///indicates weather the real time modules is currently pausing
    bool _paused;       

    SimulationTimeProvider & _simulationTimeProvider;
  public:
    SimulationTimeController(SimulationTimeProvider & simulationTimeProvider, bool startPaused = false);

    inline bool isPaused()const{ return _paused; }
    void setPause(bool flag);
    void togglePause();

    inline SimulationTimeProvider & simulationTimeProvider() {
      return _simulationTimeProvider;
    }
    /**
     * \brief allows read write access to the desired simulation speed.
     * \return .
     */
    inline Real & desiredSpeed(){return _desiredSpeed;}

    // read access to different timings

    inline const Real & realTimeFactor()const{return _realTimeFactor;}
    inline const Real & actualSpeed()const {return _actualSpeed;}
    inline const Real & desiredSpeed()const{return _desiredSpeed;}
  

    Real actualSpeedAverage();
    // overridden member of simulation task
    void timeout(Time dt,Time t);

  };

}
