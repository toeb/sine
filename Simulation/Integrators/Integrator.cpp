#include "Integrator.h"
#include <iostream>
#include <string>
using namespace std;
using namespace IBDS;

Real Integrator::integrate(Real a, Real b){
  if(_systemFunction)_systemFunction->preIntegration(a,b-a);
  _integratable->getState(_x.v);
   Real result = doIntegration(_x,_xNext,a,b);
  _integratable->setState(_xNext.v);
  if(_systemFunction)_systemFunction->postIntegration(b,b-a);
  return result;
}
void Integrator::setIntegratable(IIntegrable * integratable){
  _integratable = integratable;
  _dimension = integratable->getStateDimension();
  _x.resize(_dimension);
  _xDot.resize(_dimension);
  _xNext.resize(_dimension);
}


IIntegrable *  Integrator::getIntegratable(){
  return _integratable;
}
const VectorND & Integrator::f(Real t, const VectorND& x, Real h){
  _integratable->setState(x.v);
  if(_systemFunction)_systemFunction->evaluate(t,h);
  _integratable->getDerivedState(_xDot.v);
  return _xDot;
}

const VectorND & Integrator::getState()const{
  return _x;
}

Integrator::Integrator(): _integratable(0){
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
