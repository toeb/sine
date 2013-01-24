#pragma once
#include <core.reflection.h>
#include <core/Time.h>
namespace nspace{  
  class Timer:public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(Timer);

    PROPERTY(Time,AccumulatedTime){}
    PROPERTY(bool,IsRunning){}

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
      notifyAccumulatedTimeChanged();
    }
    void resetTimer(){
      tock();
      setAccumulatedTime(0);
    }
  };
}