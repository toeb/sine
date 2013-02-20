#include "MethodAdapter.h"

using namespace nspace;

Argument MethodAdapter::call(std::vector<Argument> args){
  return call(args);
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

Argument MethodAdapter::call(){
  std::vector<Argument> args;
  return call(args);
}
void MethodAdapter::executeAction(){
  call();
}