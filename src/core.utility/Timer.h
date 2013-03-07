#pragma once
#include <core.reflection.h>
#include <core/Time.h>
namespace nspace{  
  class Timer:public virtual PropertyChangingObject{
    reflect_type(Timer);

    typedef Time reflect_property(AccumulatedTime);
    typedef bool reflect_property(IsRunning);

    Time _startTime;

  public:
    Timer(){}
    inline void tick(){
      setIsRunning(true);
      _startTime=systemTime();
    };
    inline void tock(){
      Time endTime = systemTime();
      if(!getIsRunning())return;
      setIsRunning(false);

      _AccumulatedTime+= endTime-_startTime;
      notify_after_set(AccumulatedTime);
    }
    void resetTimer(){
      tock();
      setAccumulatedTime(0);
    }
  };
}