#include "CallableInfo.h"
#include <core.reflection.builder.h>

using namespace nspace;



auto CallableInfo::argument(unsigned int index)->argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}
auto CallableInfo::argument(unsigned int index)const ->const_argument_ptr {
  if(Arguments().size()<=index)return argument_ptr();
  return Arguments()[index];
}


bool CallableInfo::initializeType(){
  core::reflection::builder::reflect<MethodInfo>()
    ->fullyQualifiedName(DS_STRINGIFY("::"<<nspace<<"CallableInfo"))
    ->publishHierarchy();
  return true;
}
