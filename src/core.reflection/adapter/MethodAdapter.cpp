#include "MethodAdapter.h"

using namespace nspace;


MethodAdapter::MethodAdapter():_MethodInfo(0){}
MethodAdapter::MethodAdapter(Argument object, const std::string & name):MemberAdapter(object){
  auto methodInfo = object.type->getMethod(name);
  if(!methodInfo)return;
  setMethodInfo(methodInfo);
}

bool MethodAdapter::isValid()const{
  return getOwner().isValid()&& getMethodInfo()!=0;
}
MethodAdapter::MethodAdapter(Argument object, const MethodInfo * methodInfo):MemberAdapter(object){
  setMethodInfo(methodInfo);
}


Argument MethodAdapter::callImplementation(const Arguments & args){
  if(!isValid())return Argument();
  return getMethodInfo()->call(getOwner().data.get(),args);
}