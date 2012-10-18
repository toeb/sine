#include "ISimulationObject.h"
#include <algorithm>
#include <ostream>
using namespace nspace;
using namespace std;








ISimulationObject::ISimulationObject(const std::string & name): _simulation(0),_parent(0){
  setName(name);
}

ISimulationObject::ISimulationObject():_parent(0),_simulation(0){}

