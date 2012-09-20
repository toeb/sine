#pragma once
#include <simulation/ISimulationObject.h>
#include <core/Time.h>

namespace nspace{

  /**
   * \brief Timeable object.  Subclasses may measure time
   *
   */
  class Timeable : public virtual ISimulationObject{
  private:
    Time _accumulatedTime;
    Time _start;
  public:
    Timeable():_accumulatedTime(0), _start(0){}
    
    Time resetAccumulatedTime(){Time tmp = _accumulatedTime; _accumulatedTime = 0; return tmp;}

    const Time & accumulatedTime(){
      return _accumulatedTime;
    }

    /**
     * \brief start time measurement
     */
    inline void tick(){
      _start = applicationTime();
    }

    /**
     * \brief ends time measurement
     */
    inline void tock(){
      _accumulatedTime +=  applicationTime()-_start;
    }
    
  };
}
