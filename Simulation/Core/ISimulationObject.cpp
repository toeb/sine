#include "ISimulationObject.h"
using namespace IBDS;



const TypeId ISimulationObject::getType()const{
  static const TypeId type="ISimulationObject";
  return type;
}


ISimulationObject::ISimulationObject():_name(0), _initialized(false){}
ISimulationObject::~ISimulationObject(){delete _name;}
void ISimulationObject::setName(const std::string & name ){
  if(!name.compare("")){
    _name=0;
    return;
  }
  _name = new std::string(name);
}
  
const std::string* ISimulationObject::getName()const{return _name;}

bool ISimulationObject::initialize(){
  if(_initialized){
    return true;
  }
  _initialized = initializeObject();
  return _initialized;
};

bool ISimulationObject::isInitialized()const{
  return _initialized;
}


void ISimulationObject::cleanup(){
  cleanupObject();
  _initialized = false;
};