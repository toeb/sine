#pragma once

#include <core.task/Task.h>
#include <core/Time.h>
#include <functional>
namespace nspace{
  class ExtendedTask :public virtual Task{
    TYPED_OBJECT(ExtendedTask);
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

  class DelegateTask : public virtual ExtendedTask{
    TYPED_OBJECT(ExtendedTask);
  private:
    std::function<void () > _action;
  public:
    DelegateTask(std::function<void()> callback):_action(callback){}
  public:
    void runTask(){_action();}
  };
}