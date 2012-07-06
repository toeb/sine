#include "Simulation.h"
#include <algorithm>
#include <Simulation/Core/CompositeSimulationObject.h>
using namespace IBDS;
using namespace std;


Simulation::Simulation():
  _time(0),
  _targetTime(0),
  _integrator(0)
{
}

ISimulationObject * Simulation::find(const std::string & name){
  for(auto it = _simulationObjects.begin(); it != _simulationObjects.end(); it++){
    ISimulationObject * object = *it;
    if(*object->getName() == name)return object;
  }
  return 0;
}

void Simulation::setIntegrator(Integrator & integrator){
  _integrator = &integrator;
}
Integrator * Simulation::getIntegrator(){
  return _integrator;
}

Simulation::~Simulation(){}

bool Simulation::addSimulationModule(ISimulationModule * module){
  for(auto it = _simulationModules.begin(); it != _simulationModules.end(); it++){
    if(!(*it)->isCompatibleWith(module))return false;
  }
  _simulationModules.insert(module);
  // add all existing sim objects to new algorithm
  for(auto it = _simulationObjects.begin(); it!=_simulationObjects.end(); it++){
    module->add(*it);
  }

  return true;
}

bool Simulation::removeSimulationModule(ISimulationModule * module){  
  auto pos = std::find(_simulationModules.begin(), _simulationModules.end(), module);
  if(pos==_simulationModules.end())return false;


  for(auto it = _simulationObjects.begin(); it!=_simulationObjects.end(); it++){
    module->remove(*it);
  }

  return true;
}

void Simulation::foreachModule(std::function<void(ISimulationModule*)> f){
  for_each(_simulationModules.begin(), _simulationModules.end(),f);
}
void Simulation::foreachObject(std::function<void(ISimulationObject*)> f){
  for_each(_simulationObjects.begin(), _simulationObjects.end(),f);
}

bool Simulation::add(ISimulationObject * object){
  bool objectWasAdded = false;
  

  if(!_simulationObjects.insert(object).second)return false;


  auto composite = dynamic_cast<CompositeSimulationObject*>(object);
  if(composite){
    composite->forEachChild([this](ISimulationObject* child){
      add(child);
    });
  }

  auto simulationModule = dynamic_cast<ISimulationModule*>(object);
  if(simulationModule){
    addSimulationModule(simulationModule);
    objectWasAdded = true;
  }
  //tries to add the new object to every module.
  for(auto it = _simulationModules.begin(); it != _simulationModules.end(); it++){
    if( (*it)->add(object)){
      objectWasAdded=true;
    }
  }  
 
  onSimulationObjectAdded(object);
  return objectWasAdded;
}
bool Simulation::remove(ISimulationObject * object){

  auto pos = std::find(_simulationObjects.begin(), _simulationObjects.end(), object);
  if(pos==_simulationObjects.end())return false;

  
  for(auto it = _simulationModules.begin(); it != _simulationModules.end(); it++){
    if((*it)->remove(object));
  }

  auto simulationModule = dynamic_cast<ISimulationModule*>(object);
  if(simulationModule)removeSimulationModule(simulationModule);

  onSimulationObjectRemoved(object);
  return true;
}


const Real & Simulation::getTargetTime(){return _targetTime;}
const Real & Simulation::time(){return _time;}

Real Simulation::elapsedSystemTime()const{return currentTime()-_initialSystemTime;}

void Simulation::simulate(Real targetTime){
  
  if(targetTime < _time)return;
  _targetTime = targetTime;

  if(_integrator){
    _time =_integrator->integrate(_time,_targetTime);
  }

}

bool Simulation::initializeObject(){
  bool success = true;
  foreachObject([&success](ISimulationObject * o){success &= o->initialize();});
  _initialSystemTime = currentTime();
  return success;
}