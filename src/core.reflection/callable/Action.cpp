#include "Action.h"

#include <core.reflection.builder.h>
    reflect_type_default_definition(nspace::Action);

nspace::Argument nspace::Action::callImplementation(const ArgumentList & args){
  if(args.size()>0)return Argument();
  execute();
  return Argument::VoidArgument();
}
void nspace::Action::execute(){
  executeAction();
}