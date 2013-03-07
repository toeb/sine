#include "Action.h"



nspace::Argument nspace::Action::callImplementation(const Arguments & args){
  if(args.size()>0)return Argument();
  execute();
  return Argument::VoidArgument();
}
void nspace::Action::execute(){
  executeAction();
}