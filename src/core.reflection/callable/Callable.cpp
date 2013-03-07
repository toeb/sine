#include "Callable.h"


using namespace nspace;


Argument Callable::operator()(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::operator()()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::call(){
  return callImplementation(std::vector<Argument>());
}

Argument Callable::call()const{
  return callImplementation(std::vector<Argument>());
}


Argument Callable::callImplementation(const Arguments & args){return ((const Callable*)this)->callImplementation(args);};
Argument Callable::callImplementation(const Arguments & args)const{return Argument();}