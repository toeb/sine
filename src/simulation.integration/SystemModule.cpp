#include "SystemModule.h"
#include <simulation/Simulation.h>
using namespace nspace;
using namespace std;

SystemModule::SystemModule(SimulationTimeProvider & timeProvider):
_timeProvider(timeProvider),
_evaluator(0),
_integrator(0){
  
}

void SystemModule:: runTask(){
  if(!_evaluator){
    _evaluator = new Evaluator(_statefulObjects,&_systemFunction);
    _integrator->setEvaluator(_evaluator);
  }
  _integrator->setLowerBound(_timeProvider.initialTime());
  _integrator->setUpperBound(_timeProvider.targetTime());
  _timeProvider.notifyTimeReached(_integrator->step());
}


  void  SystemModule::setIntegrator(StepIntegrator * integrator){
    Real lower=0;
    Real upper=0;
    if(_integrator){
      lower = _integrator->lowerBound();
      upper = _integrator->upperBound();
    }
    _integrator = integrator;
    if(_integrator){
      _integrator->setLowerBound(lower);
      _integrator->setUpperBound(upper);
    }
  }

  void  SystemModule::announce(ISimulationObject * object){
    auto stateful = dynamic_cast<StatefulObject*>(object);
    if(stateful){
      _statefulObjects.addComponent(stateful);
    }
    auto systemFunction = dynamic_cast<ISystemFunction*>(object);
    if(systemFunction){
      _systemFunction.addComponent(systemFunction);
    }
    auto integrator = dynamic_cast<StepIntegrator*>(object);
    if(integrator){
      // if integrator isn't being used
      if(integrator->evaluator())return;
      setIntegrator(integrator);
    }
  }

  
  bool SystemModule::initializeObject(){

    return true;
  }

 Time SystemModule::currentTime() const
  {
    if(!_integrator)return -1;
    return _integrator->t();
  }
