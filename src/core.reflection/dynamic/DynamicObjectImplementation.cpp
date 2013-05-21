#include "DynamicObjectImplementation.h"


#include <core.utility.h>
using namespace nspace;


DynamicObjectImplementation::MemberList DynamicObjectImplementation::getPropertyNames()const{
  return MemberList();
}
DynamicObjectImplementation::MemberList DynamicObjectImplementation::getMethodNames()const{
  return MemberList();
}

bool DynamicObjectImplementation::hasProperty(const std::string & name)const{
  return contains(getPropertyNames(),name);
}

bool DynamicObjectImplementation::hasMethod(const std::string & name)const{
  return contains(getMethodNames(),name);
}

Argument DynamicObjectImplementation::asArgument(){
  return Argument();
}