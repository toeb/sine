#include "MethodInfo.h"

using namespace nspace;


Argument MethodInfo::call(void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}
Argument MethodInfo::call(const void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}


