#include "Hub.h"
#include <core.hub/HubObject.h>
#include <iostream>

using namespace nspace;

void Hub::onElementAdded(Object * object){
  auto node = dynamic_cast<DataNode<Object *>* >(object);
  if(!node) node = new DataNode<Object*>(object);
  successors() |= node;
}

void Hub::onElementRemoved(Object * object){
  auto result = successors().subset([object](DataNode<Object *> * o){return o->data() == object;});
  successors() |= result;
}

Hub::Hub():DataNode<Object*>(this),_processing(false){}
Hub::~Hub(){
  foreachElement([this](Object * object){
    auto ho = dynamic_cast<HubObject*>(object);
    if(!ho)return;
    ho->_hubs /= this;
  });
}
const Set<Module*> & Hub::modules()const{return _modules;}

bool Hub::add(Object * object){
  _waitingAnnouncedObjects|=object;
  processObjects();
  return true;
}
bool Hub::remove(Object * object){
  _waitingRenouncedObjects|=object;
  processObjects();
  return true;
}

void Hub::announce(Object * object){
  if(!object)return;
  *this |= object;
}
void Hub::renounce(Object * object){
  if(!object)return;
  *this /= object;
}

void Hub::processObjects(){
  if(_processing)return;
  _processing = true;
  while(_waitingRenouncedObjects.size()){
    Object * object = _waitingRenouncedObjects.first();
    processObjectRenounce(object);
    _waitingRenouncedObjects/=object;
  }
  while(_waitingAnnouncedObjects.size()){
    Object * object = _waitingAnnouncedObjects.first();
    processObjectAnnounce(object);
    _waitingAnnouncedObjects/=object;
  }
  _processing = false;
}
void Hub::processObjectAnnounce(Object  *object){
  if(!Set<Object*>::add(object))return;

  // add object to all modules
  _modules.foreachElement([object](Module * module){
    module->announce(object);
  });

  auto module = dynamic_cast<Module * > (object);
  // process module
  if(module){
    // add module to module list
    _modules |= module;
    // add every object to the module
    foreachElement([module](Object * o){
      if(module==o)return;
      module->announce(o);
    });
  }

  //
  auto hubObject = dynamic_cast<HubObject*>(object);
  if(hubObject){
    hubObject->_hubs |=this;
    hubObject->onAddedToHub(*this);
  }
}

void Hub::processObjectRenounce(Object  *object){
  // important to stop recursion
  if(!Set<Object*>::remove(object))return;

  auto module = dynamic_cast<Module * > (object);
  if(module){
    _modules /= module;
    foreachElement([module](Object * o){
      module->renounce(o);
    });
  }
  _modules.foreachElement([object](Module * module){
    module->renounce(object);
  });
  auto hubObject = dynamic_cast<HubObject*>(object);
  if(hubObject){
    hubObject->_hubs /=this;
    hubObject->onRemovedFromHub(*this);
  }
}