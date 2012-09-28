#pragma once

#include <simulation.time/ITimeProvider.h>
#include <simulation/SimulationTask.h>
#include <simulation.time/RealTimeProvider.h>
#include <math.statistics/AverageOverTime.h>

#include <functional>
namespace nspace{

class PeriodicTask : public SimulationTask{
private:
  const ITimeProvider & _timeProvider;
  Time _lastRunTime;
  Time _lastCallTime;
  Real _actualFrequency;
  Time _timeoutInterval;
  AverageOverTime _actualFrequencyAverage;
  AverageOverTime _callFrequencyAverage;

public:
  PeriodicTask( Time timeoutInterval=0,const ITimeProvider & provider = RealTimeProvider::defaultInstance()):
      _timeProvider(provider),
      _lastCallTime(0),
      _lastRunTime(0),
      _actualFrequency(0),
      _timeoutInterval(timeoutInterval),
      _callFrequencyAverage(1.0),
      _actualFrequencyAverage(1.0){

      }

  inline const ITimeProvider & timeProvider()const{return _timeProvider;}
  
  Real actualFrequencyAverage(){
    return _actualFrequencyAverage.calculate();
  }
  Real callFrequencyAverage(){
    return _callFrequencyAverage.calculate();
  }

  inline Real frequency()const{
    return _actualFrequency;
  }
  inline Time interval()const{return _timeoutInterval;}
  inline Time & interval(){
    return _timeoutInterval;
  }
  inline Time nextRunTime()const{
    Time result = interval() - timeSinceLastRun();
    return result;
  }
  inline Time lastRunTime()const{
    return _lastRunTime;
  }
  inline Time timeSinceLastRun()const{
    return _timeProvider.time()-_lastRunTime;
  }

  void setDesiredFrequency(Real frequency){
    interval() = 1.0/frequency;
  }
  Real desiredFrequency()const{
    return 1.0/interval();
  }
  virtual void timeout(Time timePassed, Time time)=0;
  
  void runTask(){
    Time t = timeProvider().time();
    Time dt_call = t-_lastCallTime;
    _lastCallTime = t;
    Real f_call = 1.0/dt_call;
    _callFrequencyAverage.addSample(f_call);
    Time dt_run = t-_lastRunTime;
    if(interval() > dt_run)return;
    timeout(dt_run,t); 
    _lastRunTime = t;
    _actualFrequency = 1.0/dt_run;
    _actualFrequencyAverage.addSample(_actualFrequency);
  }
};

class PeriodicTaskDelegate : public PeriodicTask{
private:
  std::function<void (Time,Time)> _callback;
  bool _repeat;
  bool _executed;
public:

  /**
   * \brief Constructor.
   * 
   * \param callback        The callback function to be called.
   * \param timeoutInterval (optional) the timeout interval.
   * \param timeProvider    (optional) the time provider.
   */
  PeriodicTaskDelegate(
    std::function<void (Time,Time)> callback,  
    Time timeoutInterval=0,
    bool repeat = true,
    const ITimeProvider & timeProvider=RealTimeProvider::defaultInstance()
    )
    :
    PeriodicTask(timeoutInterval,timeProvider),
      _repeat(repeat),
      _executed(false),
    _callback(callback){
  }

  void timeout( Time timePassed , Time time ){
    if(_executed && !_repeat)return;      
    _callback(timePassed,time);    
    _executed = true;
  }

};



}

