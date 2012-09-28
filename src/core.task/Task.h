#pragma once

#include <core/Object.h>
#include <core.task/ITask.h>
namespace nspace{
  class Task : public virtual Object, public virtual ITask{
    TYPED_OBJECT;
  protected:
    virtual void onBeforeRun();
    virtual void onAfterRun();
    virtual bool canRunTask();
  public:
    void run();
    virtual void runTask()=0;
  };
}