#include "DynamicBody.h"
using namespace nspace;

bool DynamicBody::isFixed()const{
  return getMass()==0;
}