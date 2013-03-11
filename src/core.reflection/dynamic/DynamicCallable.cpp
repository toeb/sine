#include "DynamicCallable.h"
#include <core.reflection/dynamic/DynamicCallableImplementation.h>
using namespace nspace;



struct DynamicCallableSmartPointer:public DynamicCallableImplementation{
  std::shared_ptr<Callable> callable;
  DynamicCallableSmartPointer(std::shared_ptr<Callable> callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const Arguments & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const Arguments & args) const override final{
    return callable->callImplementation(args);
  }
};

struct DynamicCallableRawPointer:public DynamicCallableImplementation{
  Callable * callable;
  DynamicCallableRawPointer(Callable * callable):callable(callable){}
  bool isValid() const override final{
    return callable->isValid();
  }
  Argument callImplementation(const Arguments & args) override final{
    return callable->callImplementation(args);
  }
  Argument callImplementation(const Arguments & args) const override final{
    return callable->callImplementation(args);
  }
};



DynamicCallable::DynamicCallable(std::shared_ptr<Callable> callable):implementation(new DynamicCallableSmartPointer(callable)){}
DynamicCallable::DynamicCallable(Callable * callable):implementation(new DynamicCallableRawPointer(callable)){}
DynamicCallable::DynamicCallable(Callable & callable):implementation(new DynamicCallableRawPointer(&callable)){}

DynamicCallable::DynamicCallable(std::shared_ptr<DynamicCallableImplementation> impl):implementation(impl){}
DynamicCallable::DynamicCallable(){}


bool DynamicCallable::isValid()const {return (bool)implementation&&implementation->isValid();}
Argument DynamicCallable::callImplementation(const Arguments &args){return implementation->callImplementation(args);}