#include "DynamicObject.h"
#include "DynamicObjectImplementation.h"
using namespace nspace;


DynamicObject::DynamicObject(std::shared_ptr<DynamicObjectImplementation> impl):_implementation(impl){}


Argument DynamicObject::operator[](const std::string & name){
  return getProperty(name);
}

Argument DynamicObject::getProperty(const std::string & name){
  return _implementation->getMember(name);
}
DynamicCallable DynamicObject::getMethod(const std::string & name){
  return getProperty(name);
}

DynamicObject::MemberList DynamicObject::getMemberNames(){
  return _implementation->getMemberNames();
}