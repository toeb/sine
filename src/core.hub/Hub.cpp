#include "Hub.h"
#include <core.hub/HubObject.h>
using namespace nspace;

Hub & Hub::operator << (Object * object){
  announce(object);
  return *this;
}
Hub & Hub::operator << (Object & object){
  announce(&object);
  return *this;
}



Hub::Hub(){}    
const Set<Module*> & Hub::modules()const{return _modules;}
const Set<Object*> & Hub::objects()const{return _objects;}


void Hub::announce(Object * object){
  if(!object)return;
  _waitingAnnouncedObjects.push(object);
  processObjects();
}
void Hub::renounce(Object * object){
  _waitingRenouncedObjects.push(object);
  processObjects();
}

void Hub::processObjects(){
  while(_waitingRenouncedObjects.size()){
    processObjectRenounce(_waitingRenouncedObjects.front());
    _waitingRenouncedObjects.pop();
  }
  while(_waitingAnnouncedObjects.size()){
    processObjectAnnounce(_waitingAnnouncedObjects.front());
    _waitingAnnouncedObjects.pop();
  }
}
void Hub::processObjectAnnounce(Object  *object){
  if(_objects.contains(object))return;
   auto module = dynamic_cast<Module * > (object);
  if(module){
    _modules |= module;
    _objects.foreachElement([module](Object * o){
      module->announce(o);
    });
  }
  _objects |= object;
  _modules.foreachElement([object](Module * module){
    module->announce(object);
  });
  
  auto hubObject = dynamic_cast<HubObject*>(object);
  if(hubObject){
    hubObject->setHub(this);
  }
}


void Hub::processObjectRenounce(Object  *object){


  auto module = dynamic_cast<Module * > (object);
  if(module){
    _modules /= module;
    _objects.foreachElement([module](Object * o){
      module->renounce(o);
    });
  }
  _modules.foreachElement([object](Module * module){
    module->renounce(object);
  });
  _objects /= object;
  auto hubObject = dynamic_cast<HubObject*>(object);
  if(hubObject){
    hubObject->setHub(0);
  }
}


