#pragma once

#include <math/AverageOverTime.h>
#include <simulation/time/ITimeProvider.h>
#include <math/AverageRate.h>
namespace nspace{
  
class SimulationTimeProvider:public virtual ITimeProvider{
private:
  Time _t_initial;
  Time _t_target;
  Time _t_actual;
  Time _lastTargetAdvance;
  Time _lastActualAdvance;
  AverageRate _averageTargetSpeed;
  AverageRate _averageActualSpeed;
public:
  SimulationTimeProvider():_averageActualSpeed(* new AverageOverTime(3)),_t_initial(0),_lastTargetAdvance(0),_lastActualAdvance(0),_t_target(0),_t_actual(0),_averageTargetSpeed(*new AverageOverTime(1)){setName("SimulationTimeProvider");}
  inline Time time()const{
    return actualTime();//return _t_target;
  }
  inline Time targetTime()const{
    return _t_target;
  }
  inline Time initialTime()const{
    return _t_initial;
  }
  inline Time simulatedTime()const{
    return _t_actual-_t_initial;
  }

  inline void advanceTo(Time t){
    if(_t_actual > t)return;
    Time t_app= applicationTime();
    Time dt_app = t_app - _lastTargetAdvance;
    _lastTargetAdvance = t_app;
    Time dt = t-_t_target;
    _averageTargetSpeed.addSample(t);
    _t_target = t;

  }
  inline void advanceBy(Time dt){
    advanceTo(targetTime()+dt);
  }
  inline void notifyTimeReached(Time t){
    Time dt=t-_t_actual;
    Time t_app = applicationTime();
    Time dt_app = t_app - _lastActualAdvance;
    _lastActualAdvance = t_app;
    _averageActualSpeed.addSample(t);
    _t_actual = t;
  }
  Time averageTargetSpeed(){return _averageTargetSpeed.calculate();}
  Time averageActualSpeed(){Time result = _averageActualSpeed.calculate();
  return result;}
  inline Time actualTime()const{return _t_actual;}
  void resetTo( Time t_sim ){
    _t_initial = t_sim;
    _t_actual = t_sim;
    _t_target = t_sim;
  }
};
}