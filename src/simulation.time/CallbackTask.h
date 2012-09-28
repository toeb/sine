#pragma once
#include <simulation.time/ITimeProvider.h>
namespace nspace{

  class CallbackTask : public SimulationTask{
  private:
    const ITimeProvider & _provider;
    Time _callbackTime;
    bool _executed;
  public:
    CallbackTask(Time callbackTime, const ITimeProvider & timeProvider):
        _provider(timeProvider),
          _executed(false),
          _callbackTime(callbackTime){

    }
    void runTask(){
      if(_executed )return;
      Time actualTime = _provider.time();
      if(_callbackTime >actualTime)return;
      executeCallback(actualTime);
      _executed = true;

    }
  protected:
    virtual void executeCallback(Time actualTime)=0;
  };
  class CallbackTaskDelegate:public CallbackTask{
  private:
    std::function<void (Time )> _callback;
  public:
    CallbackTaskDelegate(std::function<void(Time)> callback, Time callbackTime, const ITimeProvider & provider):
    CallbackTask(callbackTime,provider),_callback(callback){
      
    }

    void executeCallback( Time actualTime ){
      _callback(actualTime);
    }

  };
}