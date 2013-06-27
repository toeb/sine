#include "MethodInfo.h"

using namespace nspace;



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
}


