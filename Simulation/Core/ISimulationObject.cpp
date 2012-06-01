#include "ISimulationObject.h"
using namespace IBDS;



const TypeId ISimulationObject::getType()const{
  static const TypeId type="ISimulationObject";
  return type;
}