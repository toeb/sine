#include "ConstructorInfo.h"

using namespace nspace;


Argument ConstructorInfo::callImplementation(const ArgumentList & args){
  return MakeShared()->callImplementation(args);
}
Argument ConstructorInfo::callImplementation(const ArgumentList & args)const {
  return MakeShared()->callImplementation(args);
}

ConstructorInfo::ConstructorInfo(){
  setName("ctor");  
}

bool ConstructorInfo::isValid()const{return true;}

const std::vector<std::shared_ptr<ArgumentInfo>>& ConstructorInfo::Arguments()const{
  return _MakeShared->getArguments();
}