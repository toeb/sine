#include "ISimulationObject.h"
#include <algorithm>
#include <ostream>
using namespace nspace;
using namespace std;





void ISimulationObject::toString(ostream & out)const{
  out << "<object>"<<endl;
  out << "  <name>" << this->getName() << "</name>"<<endl;
  out << "  <type>" << this->getType() << "</type>"<<endl;
  out << "</object>" <<endl;
}


ISimulationObject::ISimulationObject(const std::string & name): _initialized(false),_simulation(0){
  setName(name);
}

ISimulationObject::ISimulationObject():_name(0), _initialized(false),_simulation(0){}
ISimulationObject::~ISimulationObject(){delete _name;}
void ISimulationObject::setName(const std::string & name ){
  if(!name.compare("")){
    _name=0;
    return;
  }
  _name = new std::string(name);
}
  
const std::string& ISimulationObject::getName()const{
  static const std::string defaultName = "<NONAME>";
  if(!_name){
    return defaultName;
  }
  return *_name;

}

bool ISimulationObject::initialize(){
  if(_initialized){
    return true;
  } 
  _initialized = initializeObject();
  if(_initialized)onObjectInitialized();
  return _initialized;
};

bool ISimulationObject::isInitialized()const{
  return _initialized;
}

void ISimulationObject::cleanup(){
  cleanupObject();
  _initialized = false;
};


bool ISimulationObject::hasName() const
{
  return _name!=0;
}
