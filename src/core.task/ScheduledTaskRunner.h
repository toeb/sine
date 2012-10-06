#pragma once

#include <core.task/ITaskRunner.h>
#include <core.task/ScheduledTask.h>
#include <queue>
namespace nspace{
  class ScheduledTaskRunner : public virtual TaskRunnerBase{
  TYPED_OBJECT(ScheduledTaskRunner);
  private:    
    std::priority_queue<ScheduledTask*,std::vector<ScheduledTask*>,ScheduledTask::CompareTaskPriority> _taskqueue;
  public:
    ScheduledTaskRunner(){}
  
  protected:
    
    virtual ITask * nextTask(){
      auto task = _taskqueue.top();
     
      _taskqueue.pop();
      return task;
    }  
    virtual void onBeforeTaskRun(ITask * task){
    
    
    }
    virtual void onAfterTaskRun(ITask * task){
      auto scheduledTask = dynamic_cast<ScheduledTask*>(task);
      if(!scheduledTask)return;
      if(scheduledTask->isOneTimeTask())return;
      scheduledTask->calculateNextTimeout(currentTime());
      _taskqueue.push(scheduledTask);
    }
    virtual bool accept(ITask * task){
      auto scheduledTask = dynamic_cast<ScheduledTask*>(task);
      if(!scheduledTask)return false;
      scheduledTask->calculateNextTimeout(currentTime());
      _taskqueue.push(scheduledTask);
      return true;
    }
    virtual bool hasTasks(){
      if(!_taskqueue.size())return false;
      ScheduledTask * front = _taskqueue.top();
      if(front->nextExecutionTime() <= currentTime())return true;
      return false;
    }
    virtual Time currentTime()const{
      return systemTime();
    }
  };
}