#pragma once

#include <core/Object.h>
#include <core.logging.h>
#include <core.task/ITask.h>
namespace nspace{
  /**
  * ITaskRunner is the base class for task runners.  It allows tasks to be added and removed
  */
  class ITaskRunner : public virtual ITask, public virtual Log{
    reflect_type(ITaskRunner);
    typedef uint reflect_property(NumberOfTasks);
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