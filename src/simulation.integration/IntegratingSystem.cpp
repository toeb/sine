#include "IntegratingSystem.h"
#include <simulation/Simulation.h>
#include <core.task/ScheduledTask.h>
#include <core.task/TaskDelegate.h>
#include <core.task/ITask.h>
#include <core.task/ITaskRunner.h>
using namespace nspace;
using namespace std;

IntegratingSystem::IntegratingSystem(SimulationTimeProvider * timeProvider):
  _Task(0),
  _SystemState(0),
  _SystemFunction(0),
  _Evaluator(0),
  _TimeProvider(0),
  _Integrator(0),
  _EvaluationCount(0)
{
  _Task=new TaskDelegate<IntegratingSystem>(*this);
  _Task->setName("Integrating System Task");
  setTimeProvider(timeProvider);
}

void IntegratingSystem::onPropertyChanged(const std::string & propertyName){
  bool ok=true;
  ok &= getEvaluator()!=0;
  ok &= getTimeProvider()!=0;
  ok &= getIntegrator()!=0;
  ok &= getTask()!=0;

  if(ok){
    Components()|=getTask();
  }
  else {
    Components()/=getTask();
  }
}

// gets called by task  steps the integrator once and notifies the timeprovider which time it reached
void IntegratingSystem::operator()(){
  if(!_TimeProvider)return;
  if(!_Integrator)return;
  debugMessage("advancing time to "<<_TimeProvider->targetTime(),8);
  _Integrator->setLowerBound(_TimeProvider->initialTime());
  _Integrator->setUpperBound(_TimeProvider->targetTime());

  _TimeProvider->notifyTimeReached(_Integrator->step());
  setEvaluationCount(getEvaluationCount()+1);
  getTask()->getTaskRunner()->addTask(getTask());
}

void IntegratingSystem::setupEvaluator(StatefulObject * state, ISystemFunction * func){
  // if there was an evaluator before delete it:
  if(_Evaluator){
    auto evaluator = _Evaluator;
    setEvaluator(0);
    delete evaluator;
  }
  // if one of the following is 0 return
  if(!state)return;
  if(!func)return;
  logInfo("Creating new Evaluator");
  // create new evaluator
  Evaluator * evaluator = new Evaluator(*state,func);
  setEvaluator(evaluator);
}

void IntegratingSystem::propertyChanging(ITask *, Task){
  // no one may change the task
  cancel=true;
}
void IntegratingSystem::propertyChanging(ISystemFunction *, SystemFunction){
  logInfo("System Function Changing");
  setupEvaluator(getSystemState(),newvalue);
  Components()/=oldvalue;
  Components()|=newvalue;
}
void IntegratingSystem::propertyChanging(StatefulObject *, SystemState){
  logInfo("Stateful Object Changing");
  setupEvaluator(newvalue,getSystemFunction());
  Components()/=oldvalue;
  Components()|=newvalue;
}
void IntegratingSystem::propertyChanging(Evaluator *, Evaluator){
  if(getIntegrator())getIntegrator()->setEvaluator(newvalue);
  Components()/=oldvalue;
  Components()|=newvalue;
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