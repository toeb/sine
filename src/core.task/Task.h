#pragma once

#include <core/Object.h>
#include <core.task/ITask.h>
namespace nspace{
  class Task : public virtual ITask{
    TYPED_OBJECT(Task);
  protected:
    virtual void onBeforeRun();
    virtual void onAfterRun();
    virtual bool canRunTask();
  public:
    void run();
    virtual void runTask()=0;
  };

  template<typename T>
  class DelegateTask : public virtual ITask, public virtual NamedObject{
    TYPED_OBJECT(DelegateTask);
    T & _function;
  public:
    DelegateTask(T & functionObject):_function(functionObject){
      setName("DelegateTask");
    }
    void run(){
      _function();
    }
  };


}