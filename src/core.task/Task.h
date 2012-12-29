#pragma once

#include <core/Object.h>
#include <core.task/ITask.h>
#include <core/NamedObject.h>
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
}
