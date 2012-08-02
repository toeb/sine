#pragma once

#include <sstream>

#include <simulation/integration/State.h>
#include <simulation/integration/IStatefulObject.h>
#include <common/Time.h>
namespace nspace{
  typedef unsigned int StateSnapshotId;
  class StateSnapshot : public ISimulationObject{
  private:
    static StateSnapshotId _currentId;
    std::string _description;
    Time _applicationTime;
    Time _simulationTime;
    Time _systemTime;
    IStatefulObject & _statefulObject;
    StateSnapshotId _id;
    State _state;
    StateSnapshot(IStatefulObject & statefulObject):_statefulObject(statefulObject),_applicationTime(0),_systemTime(0), _simulationTime(0),_id(_currentId++){
      std::stringstream ss;
      ss << "StateSnapshot-"<<_id<<std::endl;
      setName(ss.str());
    };
  public:
    IStatefulObject & statefulObject(){return _statefulObject;}
    void restore(){
      _statefulObject.importState(_state);
    }
    StateSnapshotId id()const{return _id;}
    Time applicationTime()const{return _applicationTime;}
    Time simulationTime()const{return _simulationTime;}
    Time systemTime()const{return _systemTime;}
    void setDescription(const std::string & descr){
      _description = descr;
    }
    const std::string & getDescription()const{
      return _description;
    }

    static StateSnapshot * create(Time t_sim, Time t_app,Time t_sys, IStatefulObject & statefulObject){   
      StateSnapshot * snapshot = new StateSnapshot(statefulObject);
      snapshot->_applicationTime = t_app;
      snapshot->_simulationTime = t_sim;
      snapshot->_systemTime = t_sys;

      statefulObject.resizeState(snapshot->_state);
      statefulObject.exportState(snapshot->_state);
      return snapshot;
    }
    const IState & storedState()const{
      return _state;
    }

  };

}