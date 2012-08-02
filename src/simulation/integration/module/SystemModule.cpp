#include "SystemModule.h"
#include <simulation/core/Simulation.h>
using namespace nspace;
using namespace std;

SystemModule::SystemModule(SimulationTimeProvider & timeProvider):
_timeProvider(timeProvider),
_integrator(0){
  
}

void SystemModule:: run(){
  _integrator->setLowerBound(_timeProvider.initialTime());
  _integrator->setUpperBound(_timeProvider.time());
  _timeProvider.notifyTimeReached(_integrator->step());
}


  void  SystemModule::setIntegrator(StepIntegrator * integrator){
    Real lower=0;
    Real upper=0;
    if(_integrator){
      lower = _integrator->lowerBound();
      upper = _integrator->upperBound();
      _integrator->setStatefulObject(0);
      _integrator->setSystemFunction(0);
    }
    _integrator = integrator;
    if(_integrator){
      _integrator->setStatefulObject(&_integrable);
      _integrator->setSystemFunction(&_systemFunction);
      _integrator->setLowerBound(lower);
      _integrator->setUpperBound(upper);
    }
  }

  void  SystemModule::announce(ISimulationObject * object){
    auto integrable = dynamic_cast<IStatefulObject*>(object);
    if(integrable){
      _integrable.addComponent(integrable);
    }
    auto systemFunction = dynamic_cast<ISystemFunction*>(object);
    if(systemFunction){
      _systemFunction.addComponent(systemFunction);
    }
    auto integrator = dynamic_cast<StepIntegrator*>(object);
    if(integrator){
      // if integrator isn't being used
      if(integrator->statefulObject())return;
      if(integrator->getSystemFunction())return ;
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
