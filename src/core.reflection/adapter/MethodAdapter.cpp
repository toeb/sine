#include "MethodAdapter.h"

using namespace nspace;


MethodAdapter::MethodAdapter():_MethodInfo(0){}
MethodAdapter::MethodAdapter(Argument object, const std::string & name):
  MemberAdapter(object),
  _MethodInfo(object.type->getMethod(name))
{

}

bool MethodAdapter::isValid()const{
  return getOwner().isValid()&& getMethodInfo()!=0;
}
MethodAdapter::MethodAdapter(Argument object, const MethodInfo * methodInfo):
  MemberAdapter(object),
  _MethodInfo(methodInfo)
{

}


Argument MethodAdapter::callImplementation(const ArgumentList & args){
  if(!isValid())return Argument();
  return getMethodInfo()->call(getOwner().data.get(),args);
}