#include "Evaluator.h"

using namespace nspace;

Evaluator::Evaluator(StatefulObject & stateful, ISystemFunction * systemFunction):
  _statefulObject(stateful),
  _systemFunction(systemFunction){
    _statefulObject.assignState(&_state);
    _statefulObject.notifyStateNeeded();
}
void Evaluator::setX(const StateMatrix & x){
  _state.setX(x);
  _statefulObject.notifyStateChanged();
}
const StateMatrix & Evaluator::x(){
  _statefulObject.notifyStateNeeded();
  _state.getX(_x);
  return _x;
}
const StateMatrix & Evaluator::xDot(){
  _statefulObject.notifyStateNeeded();
  _state.getXDot(_xDot);
  return _xDot;
}
const StateMatrix & Evaluator::f(const StateMatrix &x, Real t, Real h){
  setX(x);
  if(_systemFunction)_systemFunction->evaluate(t,h);
  return xDot();
}