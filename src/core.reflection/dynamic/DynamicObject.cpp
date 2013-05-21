#include "DynamicObject.h"
#include "DynamicObjectImplementation.h"
#include "DynamicReflectedObjectImplementation.h"
#include "DynamicMappedObject.h"
#include <core.utility.h>
#include <core.reflection/type/Argument.implementation.template.h>
using namespace nspace;



DynamicObject::DynamicObject(std::shared_ptr<DynamicObjectImplementation> impl):_implementation(impl){}


IModifiableValue & DynamicObject::operator[](const std::string & name){
  return *getProperty(name);
}

DynamicCallable DynamicObject::getMethod(const std::string & name){
  Argument a = _implementation->getMember(name)->get();
  return a;
}


bool DynamicObject::hasMember(const std::string & name)const{ return hasProperty(name)||hasMethod(name);}
bool DynamicObject::hasProperty(const std::string & name)const{
  return _implementation->hasProperty(name);
}
bool DynamicObject::hasMethod(const std::string & name)const{
  return _implementation->hasMethod(name);
}

DynamicObject::MemberList DynamicObject::getMemberNames()const{
  return concat(getPropertyNames(),getMethodNames());
}

DynamicObject::MemberList DynamicObject::getMethodNames()const{
  return _implementation->getMethodNames();
}

DynamicObject::MemberList DynamicObject::getPropertyNames()const{
  return _implementation->getPropertyNames();
}

std::shared_ptr<IModifiableValue> DynamicObject::getProperty(const std::string & name){
  return _implementation->getMember(name);
}

std::shared_ptr<const IModifiableValue> DynamicObject::getProperty(const std::string & name)const{
  return _implementation->getMember(name);
}
Argument DynamicObject::operator*(){
  return _implementation->asArgument();
}

namespace nspace{
  DynamicObject make_dynamic_mapped(Argument arg){
    return DynamicObject(std::make_shared<DynamicMappedObjectImplementation>());
  }


  DynamicObject make_dynamic(Argument argument){
    DynamicObject result(std::make_shared<DynamicReflectedObjectImplementation>(argument));
    return result;
  }

}