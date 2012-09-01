#include "Simulation.h"
#include <iostream>
#include <algorithm>
#include <simulation/core/composites/CompositeSimulationObject.h>
#include <string>
using namespace nspace;
using namespace std;


Simulation::Simulation():_processing(false)
{
}

ISimulationObject * Simulation::find(const std::string & name){
  // go through all objects to find the one with the name.
  for(auto it = _objects.begin(); it != _objects.end(); it++){
    ISimulationObject * object = *it;
    if(object->name() == name)return object;
  }
  return 0;
}

bool Simulation::removeSimulationModule(ISimulationModule * module){   
  //find simulation module
  auto pos = std::find(_modules.begin(), _modules.end(), module);
  // if the object wasn't found then it cannot be removed thus return false
  if(pos==_modules.end())return false;
  //remove every object from the module which is to be removed
  foreachObject([module](ISimulationObject * object){module->renounce(object);});
  //remove the simulatio module from the set of modules
  _modules.erase(pos);
  // success
  return true;
}

void Simulation::toString(std::ostream & out)const{
  out<< "<simulation>"<<endl;
  out << "  <objects>"<<endl;
  foreachObjectConst([&out](ISimulationObject*  object){
    out << " <object><name>"<<object->name()<<"</name></object>"<<endl;
  });  
  out << "  </objects>"<<endl;
  out <<"</simulation>"<<endl;
}

void Simulation::add(ISimulationObject * object){
  if(!object){
		std::cerr << "tried to add null object to simulation" << std::endl;
		return ;
	}
  //set the simulation for the object added
  object->setSimulation(this);
  //add object to uninitialized objects queue
  _queue.push(object);
  // if simulation is initialized process the unititialized object queue
  if(isInitialized()) {
    processQueuedObjects();
  }
}

void Simulation::remove(ISimulationObject * object){
  // find object
  auto pos = std::find(_objects.begin(), _objects.end(), object);
  // if it is not found return false
  if(pos==_objects.end())return;
  //remove the object from all modules
  foreachModule([object](ISimulationModule * module){ module->renounce(object);});
  //if the object is a module remove the modules
  auto simulationModule = dynamic_cast<ISimulationModule*>(object);
  if(simulationModule)removeSimulationModule(simulationModule);
  //remove the object
  _objects.erase(pos);
  //call extension point
  onSimulationObjectRemoved(object);  
}

bool Simulation::initializeObject(){
  // try to initialize simulation
  if(!initializeSimulation())return false;
  //process all queued objects
  return processQueuedObjects();
}
bool Simulation::processObject(ISimulationObject * object){
  if(!_objects.insert(object).second){
    //object was already added to objects. therfore return true
    return true;
  }

  //initialize object
    if(!object->initialize()){
     cerr << "could not initialize object" <<object->name()<< endl;
      // remove object from the valid objects set
      auto it = _objects.find(object);
      _objects.erase(it);
        return false;
  }  
  if(!processComposite(object))return false;
  if(!processModule(object))return false;
 
  //call extension point method
  onSimulationObjectAdded(object);
 object->accepted();
  return true;
}


bool Simulation::processComposite(ISimulationObject * object){  
  //add all components of the composite to the simulation
  CompositeSimulationObject* composite = dynamic_cast<CompositeSimulationObject*>(object);
  //if object is not a composite return true indicating that nothing went wrong
  if(!composite)return true;
  //go through each component of the composite and add it to the simulation
  composite->foreachComponent([this](ISimulationObject* component){
    add(component);
  });  
  return true;
}

bool Simulation::processModule(ISimulationObject *  object){
  //announce object(which could be a module) to every valid module 
  foreachModule([object](ISimulationModule * module){ 
    module->announce(object);
  });
  auto module = dynamic_cast<ISimulationModule*>(object);
  // if object is not a module return true indicating that nothing went wron
  if(!module) return true;
  // else insert module into modules set
  _modules.insert(module);
  // announce all existing simulation objects to module
  foreachObject([module](ISimulationObject * simulationObject){
    module->announce(simulationObject);
  });
  return true;
}

bool Simulation::processQueuedObjects(){
  if(_processing)return true;
  _processing = true;
  // go through all waiting objects and add process them
  while(_queue.size() >0){
    ISimulationObject *  object = _queue.front();
    _queue.pop();
    //if any object was not processable return false
    if(!processObject(object)){
        cout << "could not add "<< object->name()<<" because it was not initializable"<<endl;
        return false;
    }
  }
  //else everything went ok
  _processing = false;
  return true; 
}

/**
  * \brief indexer operator returns the simulation object with the name.
  *
  * \param name The name.
  *
  * \return The indexed value.
  */
ISimulationObject * Simulation::operator[](const std::string & name){
  return find(name);
}

/**
  * \brief adds a object to the simulation
  */
Simulation & Simulation::operator <<(ISimulationObject * object){  
  if(!object){
		std::cerr << "tried to add null object to simulation" << std::endl;
		return *this;
	}
  add(object);
	return *this;
}
  /**
  * \brief adds a object to the simulation
  */
Simulation & Simulation::operator <<(ISimulationObject & object){
  add(&object);
	return *this;
}
/**
  * \brief remove the simulationobject from the simulation
  */
Simulation & Simulation::operator >>(ISimulationObject * object){
  
  remove(object);
	return *this;
}
/**
  * \brief remove the simulationobject from the simulation
  */
Simulation & Simulation::operator >>(ISimulationObject & object){
  remove(&object);
	return *this;
}


  
void Simulation::foreachModule(std::function<void(ISimulationModule*)> f){
  for_each(_modules.begin(), _modules.end(),f);
}
void Simulation::foreachObject(std::function<void(ISimulationObject*)> f){
  for_each(_objects.begin(), _objects.end(),f);
}

void Simulation::foreachObjectConst(std::function<void(ISimulationObject*)> f)const{
  for_each(_objects.begin(), _objects.end(),f);
}
