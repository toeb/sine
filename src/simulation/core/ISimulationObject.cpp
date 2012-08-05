#include "ISimulationObject.h"
#include <algorithm>
#include <ostream>
using namespace nspace;
using namespace std;





void ISimulationObject::toString(ostream & out)const{
  out << "<object>"<<endl;
  out << "  <name>" << this->getName().c_str() << "</name>"<<endl;
  out << "  <type>" << this->getType() << "</type>"<<endl;
  out << "</object>" <<endl;
}


ISimulationObject::ISimulationObject(const std::string & name): _simulation(0){
  setName(name);
}

ISimulationObject::ISimulationObject():_simulation(0){}
bool Initializable::initialize(){
  if(_initialized){
    return true;
  } 
  _initialized = initializeObject();
  if(_initialized)onObjectInitialized();
  return _initialized;
};

bool Initializable::cleanup(){
  cleanupObject();
  _initialized = false;
  return true;
};


