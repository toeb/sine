#pragma once
#include <core.task/ITask.h>
#include <core.task/ITaskRunner.h>
#include <queue>
namespace nspace{
  class SerialTaskRunner : public virtual TaskRunnerBase{
  private:
    std::queue<ITask *> _taskqueue;
  public:
    virtual bool hasTasks(){
      return _taskqueue.size()!=0;
    }
    virtual ITask * nextTask(){
      if(!hasTasks())return 0;
      ITask * task = _taskqueue.front();
      _taskqueue.pop();
    }  
    virtual bool accept(ITask * task){
      _taskqueue.push(task);
      return true;
    }
  };

}