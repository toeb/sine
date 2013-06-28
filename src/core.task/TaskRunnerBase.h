#pragma once

#include <core.task/ITaskRunner.h>

namespace nspace{
  class TaskRunnerBase : public virtual ITaskRunner,public virtual Log, public virtual NamedObject{
    reflect_type(nspace::TaskRunnerBase);
    reflect_superclasses(ITaskRunner,Log);

    typedef bool reflect_property(IsRunning);
    auto before_set(IsRunning){
      return BeforeSetAction::Cancel;
    }

    typedef uint reflect_property(NumberOfRunningTasks)
    auto before_set(NumberOfRunningTasks){return BeforeSetAction::Cancel;}

    typedef bool reflect_property(IsHalting);
    auto after_set(IsHalting){
      debugInfo("IsHalting is set to"<<getIsHalting());
    }
  public:
    TaskRunnerBase();
    void halt();
    virtual void run();
    // returns true if a task was successfully started
    bool step();
  protected:
    bool doAddTask(ITask * task);
    bool doRemoveTask(ITask * task);
    virtual ITask * nextTask(){return 0;}
    virtual void onBeforeTaskRun(ITask * task){}
    virtual void onAfterTaskRun(ITask * task){}
    virtual bool accept(ITask * task){return false;}
    virtual bool hasTasks(){return false;}
    virtual void onTaskAccepted(ITask * task){}
    virtual void onTaskRejected(ITask * task){}
    virtual void onTaskRemoved(ITask* task){}
    virtual bool canStep(){return !getNumberOfRunningTasks();}
  };
}