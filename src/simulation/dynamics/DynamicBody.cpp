#include "DynamicBody.h"
using namespace IBDS;



bool DynamicBody::isFixed()const{
  return getMass()==0;
}

