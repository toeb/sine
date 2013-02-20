#include "MethodInfo.h"

using namespace nspace;


Argument MethodInfo::call(void * object)const{
  std::vector<Argument> args;
  return call(object,args);
}

Argument MethodInfo::call(Object * object){
  auto ptr = object->getType()->toRawDerivedPointer(object);
  return call(ptr);

}