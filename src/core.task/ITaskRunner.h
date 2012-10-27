#pragma once

#include <core/Object.h>
#include <simulation.logging/Log.h>
#include <core.task/ITask.h>
namespace nspace{
  /**
  * ITaskRunner is the base class for task runners.  It allows tasks to be added and removed
  */
  class ITaskRunner : public virtual ITask, public virtual Log{
    REFLECTABLE_OBJECT(ITaskRunner);
    PROPERTY(uint,NumberOfTasks){}
  public:
    ITaskRunner();
    bool addTask(ITask * task);
    bool removeTask(ITask * task);
  protected:
    // subclasses may implement doRemoveTask
    virtual bool doRemoveTask(ITask*){return true;};
    // subclass must implement
    virtual bool doAddTask(ITask*)=0;
  };
}