#pragma once
#include <functional>
#include <core.task/ITask.h>
#include <core/Time.h>
namespace nspace{
  class ScheduledTaskRunner;
  class ScheduledTask : public virtual ITask{
  private:
    Time _interval;
    Time _lastTimeoutTime;
    Time _nextExecutionTime;
    bool _oneTimeTask;

  public:
    struct CompareTaskPriority{
    public :
      bool operator ()(const ScheduledTask * a,const ScheduledTask * b){
        return a->_nextExecutionTime > b->_nextExecutionTime;
      }
    };

    Time & interval(){
      return _interval;
    }
    Time nextExecutionTime()const{
      return _nextExecutionTime;
    }
    
    bool & isOneTimeTask(){
      return _oneTimeTask;
    }
    virtual void calculateNextTimeout(Time time){
      _lastTimeoutTime = time;
      _nextExecutionTime = time +_interval;
      // _nextExecutionTime += _timeout;
    }
    void run(){
      Time now = systemTime();
      timeout(now - _lastTimeoutTime,now);
    }

    virtual void timeout(Time dt, Time t){
      
    }
    

    ScheduledTask():_interval(0.0),_lastTimeoutTime(REAL_MAX),_nextExecutionTime(REAL_MAX),_oneTimeTask(true){}

    static bool comp(const ScheduledTask * a, const ScheduledTask * b){
      return a->nextExecutionTime() < b->nextExecutionTime();
    }

    friend class ScheduledTaskRunner;
  };

  class ScheduledTaskDelegate : public virtual ScheduledTask{
    std::function<void (Time,Time) > _callback;
  public :
    ScheduledTaskDelegate(std::function<void(Time,Time)> callback):_callback(callback){

    }
    virtual void timeout(Time dt, Time t){
      _callback(dt,t);
    }
  };

}
