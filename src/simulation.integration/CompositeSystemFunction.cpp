#include "CompositeSystemFunction.h"

using namespace nspace;

void CompositeSystemFunction::preIntegration(Time t, Time h){
  foreachComponent([&t,&h](ISystemFunction * f){
    f->preIntegration(t,h);
  });
};
void CompositeSystemFunction::evaluate(Time t, Time h){
  foreachComponent([&t,&h](ISystemFunction * f){
    f->evaluate(t,h);
  });
};
void CompositeSystemFunction::postIntegration(Time t, Time h){
  foreachComponent([&t,&h](ISystemFunction * f){
    f->evaluate(t,h);
  });
};