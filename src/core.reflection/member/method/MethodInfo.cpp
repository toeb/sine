#include "MethodInfo.h"
#include <core.reflection.builder.h>
using namespace nspace;

/*

auto MethodInfo::argument(unsigned int index)->argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}
auto MethodInfo::argument(unsigned int index)const ->const_argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}

Argument MethodInfo::call(void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}
Argument MethodInfo::call(const void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}*/

bool MethodInfo::initializeType(){
  core::reflection::builder::reflect<MethodInfo>()
    ->fullyQualifiedName(DS_STRINGIFY("::"<<nspace<<"MethodInfo"))
    ->supertype<CallableInfo>()
    ->supertype<MemberInfo>()
    ->publishHierarchy();
  return true;
}
const Type * MethodInfo::getType()const{
  return type_of<MethodInfo>();
}
Argument MethodInfo::call(void * object, std::vector<Argument> arguments)const{
  throw new std::exception("call is not implemented for member info");
}
Argument MethodInfo::call(const void * object, std::vector<Argument> arguments)const{
  throw new std::exception("const call is not implemented for member info");
}