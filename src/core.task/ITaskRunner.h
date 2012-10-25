#pragma once

#include <core/Object.h>
#include <simulation.logging/Log.h>
#include <core.task/ITask.h>
namespace nspace{

  class ITaskRunner : public virtual ITask{
    TYPED_OBJECT(ITaskRunner);

  public:
    virtual bool addTask(ITask * task)=0;
  };


  class TaskRunnerBase : public virtual ITaskRunner,public virtual Log, public virtual NamedObject{
    REFLECTABLE_OBJECT(TaskRunnerBase);
    SUBCLASSOF(Log)
  private:
    bool _running;
    bool _halting;
  public:
    TaskRunnerBase():_running(false),_halting(false){
      setName("TaskRunnerBase");
    }

    void halt(){
      _halting  =true;
    }
    bool isHalting()const{
      return _halting;
    }
    bool addTask(ITask * task){
      bool accepted= accept(task);
      if(accepted){
        onTaskAccepted(task);
        logDebug("Task Accepted: "<<*task);
      }
      else onTaskRejected(task);
      return accepted;
    }
    virtual void run(){
      if(_running)return;
      _halting = false;
      _running =true;
      while(!isHalting()){
        step();
      }
      _running = false;
    }    
    void step(){
      if(!hasTasks()){
        halt();
        return;
      }
      ITask * task = nextTask();
      if(!task)return;
      onBeforeTaskRun(task);
      if(isHalting())return;
      logDebug("Starting Task: "<<*task);
      task->run();
      logDebug("Ending Task:"<<*task);
      onAfterTaskRun(task);
    }

 
  protected:
    virtual ITask * nextTask(){return 0;}  
    virtual void onBeforeTaskRun(ITask * task){}
    virtual void onAfterTaskRun(ITask * task){}
    virtual bool accept(ITask * task){return false;}
    virtual bool hasTasks(){return false;}
    virtual void onTaskAccepted(ITask * task){}
    virtual void onTaskRejected(ITask * task){}
    
  };



}