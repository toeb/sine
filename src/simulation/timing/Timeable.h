#pragma once
#include <simulation/core/ISimulationObject.h>
#include <common/Time.h>

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
    
    void resetAccumulatedTime(){_accumulatedTime = 0;}

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
      _accumulatedTime += _start - applicationTime();
    }
    
  };
}
