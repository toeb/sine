#include "HubObject.h"

using namespace nspace;

HubObject::HubObject(){}

HubObject::~HubObject(){
  // remove hub object from every hub it is part of
  /*  Set<Hub*> h = hubs();
  h.foreachElement([this](Hub * hub){
  hub->remove(this);
  });*/
}

const Set<Hub*> & HubObject::hubs()const{return _hubs;}