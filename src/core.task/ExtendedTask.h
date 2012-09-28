#pragma once

#include <core.task/Task.h>
#include <core/Time.h>
namespace nspace{
  class ExtendedTask :public virtual Task{
    TYPED_OBJECT;
  private :
    long _runCount;
    Time _runTime;
    Time _lastStartTime;
    bool _running;
  public:
    ExtendedTask();
    virtual void toString(std::ostream & o)const;
  protected:
    
    void onBeforeRun();
    void onAfterRun();

  };
}