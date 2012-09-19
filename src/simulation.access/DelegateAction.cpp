#include "DelegateAction.h"

using namespace std;
using namespace nspace;

DelegateAction::DelegateAction(const string & name, function<void()>  function):IAction(name){
  _function = function;
}
void DelegateAction::execute(){
  _function();
}