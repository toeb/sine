#include "SingleStepIntegrator.h"

using namespace IBDS;


 Real SingleStepIntegrator::doIntegration(const VectorND& x_0, VectorND& x_i, Real  a, Real b){
  Real t = a;
  x_i = x_0;
  
  ISystemFunction  * systemFunction = getSystemFunction();
  while(t < b){
    systemFunction->preIntegration(t,_h);
    getIntegratable()->getState(x_i.v);
    doStep(t,x_i,_h);
    t +=_h;
    getIntegratable()->setState(x_i.v);
    systemFunction->postIntegration(t,_h);
  }
  return t;
}
 Real SingleStepIntegrator::getStepSize(){
   return _h;
 }
 void SingleStepIntegrator::setStepSize(Real h){
    _h=h;
 }
