#pragma once
#include <simulation/core/ISimulationObject.h>
#include <simulation/history/StateSnapshot.h>
#include <simulation/time/SimulationTimeProvider.h>
#include <simulation/integration/IStatefulObject.h>
#include <simulation/time/PeriodicTask.h>
#include <simulation/core/Simulation.h>
#include <simulation/time/CallbackTask.h>
#include <vector>
#include <algorithm>
namespace nspace{
  class HistoryModule:public ISimulationObject, public virtual Composite<StateSnapshot>{
  private:
    IStatefulObject & _statefulObject;
    SimulationTimeProvider & _simulationTime;
  public:
    IStatefulObject & statefulObject(){return _statefulObject;}
    HistoryModule(IStatefulObject & stateobject, SimulationTimeProvider & simulationTime):_statefulObject(stateobject),_simulationTime(simulationTime){

    }
    StateSnapshot * snapshot(){
      auto snapshot = StateSnapshot::create(_simulationTime.time(),applicationTime(),systemTime(),_statefulObject);
      addComponent(snapshot);
      simulation()->add(snapshot);
      return snapshot;
    }
    void snapshotAt(Time t_sim){
      
      Time timeout = t_sim-_simulationTime.time();

      CallbackTaskDelegate * del = new CallbackTaskDelegate([this](Time timePassed){
        snapshot();        
      },t_sim,_simulationTime);

      *simulation()<<del;
    }

    
    StateSnapshot * restoreState(Real simulationTime){
      StateSnapshot * result=findSnapshot(simulationTime);
      if(!result)return result;
      restoreState(*result);
    }
    StateSnapshot *  restoreState(StateSnapshotId id){
      StateSnapshot * result=findSnapshot(id);
      if(!result)return result;
      restoreState(*result);
    }
    StateSnapshot * findSnapshot(StateSnapshotId id){
      for(auto it = components().begin(); it != components().end(); it++){
        auto snapshot = *it;
        if(snapshot->id()==id){
          return snapshot;
        }
      }
      return 0;
    }
    StateSnapshot * findSnapshot(Time simulationTime){
      Time closestTime = DBL_MAX;
      StateSnapshot * result=0;
      for(auto it = components().begin(); it != components().end(); it++){
        auto snapshot = *it;
        Time diff = simulationTime - snapshot->simulationTime();
        if(diff < 0)continue;
        if(diff > closestTime)continue;
        closestTime = diff;
        result = snapshot;
      }
      return result;
    }
    void restoreState(StateSnapshot & snapshot){
      snapshot.restore();
      _simulationTime.resetTo(snapshot.simulationTime());
      
    }



  };
}