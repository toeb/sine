#pragma once

#include <core.task/Task.h>
#include <core/Time.h>
#include <functional>
namespace nspace{
  class ExtendedTask :public virtual Task, public virtual PropertyChangingObject{
    reflect_type(ExtendedTask);
    typedef long reflect_property(RunCount);
    typedef Time reflect_property(RunTime);
    typedef Time reflect_property(LastStartTime);
    typedef bool reflect_property(IsRunning);
  private :

  public:
    ExtendedTask();
    virtual void toString(std::ostream & o)const;
  protected:

    void onBeforeRun();
    void onAfterRun();
  };
}