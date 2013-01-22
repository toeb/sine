#pragma once

#include <core/Time.h>

#include <simulation/ISimulationObject.h>
#include <simulation/SimulationModuleBase.h>

#include <simulation.state/StatefulObject.h>
namespace nspace{
  // interface for the system function.
  class ISystemFunction : public virtual ISimulationObject{
    TYPED_OBJECT(ISystemFunction);
  public:
    // called before integration step
    virtual void preIntegration(Time t, Time h){};
    virtual void evaluate(Time t, Time h)=0;
    // called after integration step
    virtual void postIntegration(Time t, Time h){};
    // log system info
    virtual void logSystemInfo(std::ostream & ostream)const{};
  };
}


/*

class TrajectorySystemFunction : public virtual ISystemFunction, public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(TrajectorySystemFunction);
public:
  typedef Function<StateMatrix,Real> Trajectory;
  SIMPLE_PROPERTY(Trajectory*, Trajectory){}
  SIMPLE_PROPERTY(StatefulObject*, StatefulObject){}
public:

  TrajectorySystemFunction():_Trajectory(0),_StatefulObject(0){

  }
  virtual void evaluate(Time t, Time h){
    auto trajectory = getTrajectory();
    auto state=getStatefulObject();
    if(!trajectory)return;
    if(!state)return;
    VectorND x;
    trajectory->evaluate(x,t);
  }
};*/