#pragma once

#include <core.task/ITaskRunner.h>

namespace nspace{
  class TaskRunnerBase : public virtual ITaskRunner,public virtual Log, public virtual NamedObject{
    REFLECTABLE_OBJECT(TaskRunnerBase);
    SUBCLASSOF(ITaskRunner);
    PROPERTY(bool, IsRunning){cancel=true;}

    PROPERTY(uint, NumberOfRunningTasks){cancel=true;}
    PROPERTY(bool, IsHalting){debugInfo("IsHalting is set to"<<newvalue);}
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