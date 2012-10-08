#pragma once

#include <core/Object.h>

#include <core.task/ITask.h>
namespace nspace{

  class ITaskRunner : public virtual ITask{
    TYPED_OBJECT(ITaskRunner);
  public:
    virtual bool addTask(ITask * task)=0;
  };


  class TaskRunnerBase : public virtual ITaskRunner{
    TYPED_OBJECT(TaskRunnerBase);
  private:
    bool _running;
    bool _halting;
  public:
    TaskRunnerBase():_running(false),_halting(false){

    }

    void halt(){
      _halting  =true;
    }
    bool isHalting()const{
      return _halting;
    }
    bool addTask(ITask * task){
      bool accepted= accept(task);
      if(accepted)onTaskAccepted(task);
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
      
      task->run();
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