#include "MethodAdapter.h"

using namespace nspace;

Argument MethodAdapter::call(std::vector<Argument> args){
  auto method = getMethodInfo();
  auto owner = getOwner();
  return method->call(owner.data.get(),args);
}

MethodAdapter::MethodAdapter():_MethodInfo(0){}
MethodAdapter::MethodAdapter(Argument object, const std::string & name):MemberAdapter(object){
  auto methodInfo = object.type->getMethod(name);
  if(!methodInfo)return;
  setMethodInfo(methodInfo);
}
MethodAdapter::MethodAdapter(Argument object, const MethodInfo * methodInfo):MemberAdapter(object){
  setMethodInfo(methodInfo);
}

Argument MethodAdapter::call(){
  std::vector<Argument> args;
  return call(args);
}
void MethodAdapter::executeAction(){
  call();
}