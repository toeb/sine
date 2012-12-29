#include "ModuleBase.h"

using namespace nspace;

const Set<Object*> & ModuleBase::objects()const{return _objects;}

void ModuleBase::announce(Object * object){
  onAnnounce(object);
  if(accept(object)){
    _objects |= object;
    onAcception(object);
  }else{
    onRejection(object);
  }
}
void ModuleBase::renounce(Object * object){
  if(_objects.contains(object)){
    onBeforeRenounce(object);
  }
  if(_objects.remove(object)){
    onRenounce(object);
  }
}