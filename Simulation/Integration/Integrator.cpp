#include "Integrator.h"
#include <iostream>
#include <string>
using namespace std;
using namespace IBDS;

Real Integrator::getSuggestedStepSize()const{
  return _suggestedStepSize;
}
void Integrator::setSuggestedStepSize(Real h){
  _suggestedStepSize= h;
  onSuggestedStepSizeChanged();
}

void Integrator::updateStateSize(){  
  _dimension = _integratable->getStateDimension();
  _x.resize(_dimension);
  _xDot.resize(_dimension);
  _xNext.resize(_dimension);
}
Real Integrator::integrate(Real a, Real b){
  tick();

  if(_integratable->hasStateDimensionChanged())updateStateSize();
 
  _integratable->getState(_x.v);
   Real result = doIntegration(_x,_xNext,a,b);
  _integratable->setState(_xNext.v);
 
  tock();
  return result;
}
void Integrator::setIntegratable(IIntegrable * integratable){
  _integratable = integratable;
  updateStateSize();
}


IIntegrable *  Integrator::getIntegratable(){
  return _integratable;
}
const VectorND & Integrator::f(Real t, const VectorND& x, Real h){
  _integratable->setState(x.v);
  tock();
  if(_systemFunction)_systemFunction->evaluate(t,h);
  tick();
  _integratable->getDerivedState(_xDot.v);
  
  return _xDot;
}

const VectorND & Integrator::getState()const{
  return _x;
}

Integrator::Integrator(): _integratable(0),_suggestedStepSize(0.01){
  setName("Integrator");
}

Integrator::~Integrator(){
}

void Integrator::setSystemFunction(ISystemFunction  & function){
  setIntegratable(&(function.getIntegrable()));
  _systemFunction = &function;

}
ISystemFunction * Integrator::getSystemFunction(){
  return _systemFunction;
}
