#include "SystemModule.h"
#include <simulation/Simulation.h>
#include <core.task/ScheduledTask.h>
#include <core.task/Task.h>
using namespace nspace;
using namespace std;

IntegratingSystem::IntegratingSystem(SimulationTimeProvider * timeProvider):
  _Integrator(0),
  _TimeProvider(0),
  _Evaluator(0),
  _Task(0),
  _State(0),
  _SystemFunction(0)  
{
  _Task=new DelegateTask<IntegratingSystem>(*this);
  setTimeProvider(timeProvider);
} 
// gets called by task  steps the integrator once and notifies the timeprovider which time it reached
void IntegratingSystem::operator()(){
  if(!_TimeProvider)return;
  if(!_Integrator)return;
  _Integrator->setLowerBound(_TimeProvider->initialTime());
  _Integrator->setUpperBound(_TimeProvider->targetTime());
  _TimeProvider->notifyTimeReached(_Integrator->step());
}

void IntegratingSystem::setupEvaluator(StatefulObject * state, ISystemFunction * func){
  // if there was an evaluator before delete it:
  if(_Evaluator){
    auto evaluator = _Evaluator;
    setEvaluator(0);
    delete evaluator;
  }
  // if one of the following is 0 return
  if(!(state&&func))return;
  // create new evaluator
  Evaluator * evaluator = new Evaluator(*getState(),getSystemFunction());
  setEvaluator(evaluator);  
}

void IntegratingSystem::propertyChanging(ITask *, Task){
  // no one may change the task
  cancel=true;
}
void IntegratingSystem::propertyChanging(ISystemFunction *, SystemFunction){
  setupEvaluator(getState(),newvalue);
}
void IntegratingSystem::propertyChanging(StatefulObject *, State){
  setupEvaluator(newvalue,getSystemFunction());
}
void IntegratingSystem::propertyChanging(Evaluator *, Evaluator){
  if(getIntegrator())getIntegrator()->setEvaluator(newvalue);
}
void IntegratingSystem::propertyChanging(SimulationTimeProvider *, TimeProvider){
  // add task only if both integratpr and timeprovider are set
  if(newvalue && getIntegrator())Components()|=getTask();
  else Components()/=getTask();
}
void IntegratingSystem::propertyChanging(StepIntegrator *, Integrator){
  if(oldvalue)oldvalue->setEvaluator(0);
  if(newvalue)newvalue->setEvaluator(getEvaluator());
  // add task only if both integratpr and timeprovider are set
  if(newvalue && getTimeProvider())Components()/=getTask();
  else Components()|=getTask();
}

