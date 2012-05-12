#include "Integrator.h"
#include <iostream>
#include <string>
using namespace std;
using namespace IBDS;

void Integrator::integrate(const Real & a, const Real & b){
  _integratable->getState(_x.v);
   doIntegration(_x,_xNext,a,b);
  _integratable->setState(_xNext.v);
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
const VectorND & Integrator::f(const VectorND& x){
  _integratable->setState(x.v);
  _integratable->evaluate();
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
