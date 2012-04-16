#include "Integrator.h"
#include <iostream>
using namespace std;
using namespace IBDS;
const string & Integrator::getName()const{
  return _name;
}
void Integrator::setName(const string & name){
  _name = *(new string( name));
}
void Integrator::integrate(const Real & a, const Real & b){

  _integratable->getState(_x->v);
   doIntegration(*_x,*_xNext,a,b);
  _integratable->setState(_xNext->v);
}
void Integrator::setIntegratable(IIntegrable * integratable){
  _integratable = integratable;
  _dimension = integratable->getStateDimension();
  _x = new VectorND(_dimension);
  _xDot = new VectorND(_dimension);
  _xNext = new VectorND(_dimension);
}
IIntegrable *  Integrator::getIntegratable(){
  return _integratable;
}
const VectorND & Integrator::f(const VectorND& x){
  _integratable->setState(x.v);
  _integratable->evaluate();
  _integratable->getDerivedState(_xDot->v);
  return *_xDot;
}

const VectorND & Integrator::getState()const{
  return *_x;
}

Integrator::Integrator(): _integratable(0), _x(0), _xDot(0), _xNext(0),_name(*new std::string("Integrator")){
}
Integrator::~Integrator(){
}
