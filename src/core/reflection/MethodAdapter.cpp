#include "MethodAdapter.h"

using namespace nspace;

const MethodInfo & MethodAdapter::methodInfo()const{
  return _methodInfo;
}
Object * MethodAdapter::object(){
  return _object;
}
MethodAdapter::MethodAdapter(Object * object, const MethodInfo & method):_object(object), _methodInfo(method){

}

bool MethodAdapter::call(void * arguments , void **returnvalue){
  return  _methodInfo.call(_object,arguments,returnvalue);
}