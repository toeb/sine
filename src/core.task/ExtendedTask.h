#pragma once

#include <core.task/Task.h>
#include <core/Time.h>
#include <functional>
namespace nspace{
  class ExtendedTask :public virtual Task, public virtual PropertyChangingObject{
    TYPED_OBJECT(ExtendedTask);
    PROPERTY(long, RunCount){}
    PROPERTY(Time, RunTime){}
    PROPERTY(Time, LastStartTime){}
    PROPERTY(bool, IsRunning){}
  private :

  public:
    ExtendedTask();
    virtual void toString(std::ostream & o)const;
  protected:

    void onBeforeRun();
    void onAfterRun();
  };
}