#include "Callable.h"


using namespace nspace;


Argument Callable::operator()(){
  return operator()(std::vector<Argument>());
}

Argument Callable::operator()()const{
  return operator()(std::vector<Argument>());
}


Argument Callable::call(){
  return operator()(std::vector<Argument>());
}

Argument Callable::call()const{
  return operator()(std::vector<Argument>());
}


Argument Callable::callImplementation(const Arguments & args){return ((const Callable*)this)->callImplementation(args);};
Argument Callable::callImplementation(const Arguments & args)const{return Argument();}