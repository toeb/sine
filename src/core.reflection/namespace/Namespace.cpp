#include "Namespace.h"

using namespace nspace;


Namespace::Namespace(int i):_Name(""),_FullyQualifiedName(""),_ParentNamespace(0),_IsType(false){}

const Namespace* Namespace::Global(){
  static Namespace globalNamepsace(0);
  return &globalNamepsace;
}



Namespace::Namespace(const std::string & name, const Namespace * parent):_IsType(false){
  setParentNamespace(parent);
  const_cast<Namespace*>(parent)->_Namespaces|=this;
  setName(name);
  if(parent==Global())setFullyQualifiedName(name);
  else setFullyQualifiedName(DS_INLINE_STRING(parent->getFullyQualifiedName()<<"::"<<getName()));
}


