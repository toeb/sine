#pragma once

#include <core.task/TaskRunnerBase.h>
#include <core.task/ScheduledTask.h>
#include <queue>
namespace nspace{
  // Implementation of TaskRunner which schedules tasks to be executed at specific timepoints
  class ScheduledTaskRunner : public virtual TaskRunnerBase{
    reflect_type(nspace::ScheduledTaskRunner);
    reflect_superclasses(TaskRunnerBase)
  private:
    std::priority_queue<ScheduledTask*,std::vector<ScheduledTask*>,ScheduledTask::CompareTaskPriority> _taskqueue;
  public:
    ScheduledTaskRunner();
  protected:
    virtual ITask * nextTask();
    virtual void onBeforeTaskRun(ITask * task);
    virtual void onAfterTaskRun(ITask * task);
    virtual bool accept(ITask * task);
    virtual bool hasTasks();
    virtual Time currentTime()const;
  };
}