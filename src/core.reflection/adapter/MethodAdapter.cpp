#include "MethodAdapter.h"

#include <core.reflection/type/TypeInfo.h>

using namespace nspace;

bool MethodAdapter::call(void * arguments , void **returnvalue){
  auto object = getOwner();
  auto method = getMethodInfo();
  return  method->call(object,arguments,returnvalue);
}

MethodAdapter::MethodAdapter():_MethodInfo(0){}
MethodAdapter::MethodAdapter(Object * object, const std::string & name){
  setOwner(object);
  auto methodInfo = object->getType()->getMethodInfo(name);
  if(!methodInfo)return;
  setMethodInfo(methodInfo);
}
MethodAdapter::MethodAdapter(Object * object, const MethodInfo * methodInfo){
  setMethodInfo(methodInfo);
  setOwner(object);
}

void MethodAdapter::executeAction(){
  call(0,0);
}