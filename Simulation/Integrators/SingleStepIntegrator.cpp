#include "SingleStepIntegrator.h"

using namespace IBDS;


 Real SingleStepIntegrator::doIntegration(const VectorND& x_0, VectorND& x_i, Real  a, Real b){
  Real t = a;
  x_i = x_0;
  while(t < b){
    doStep(t,x_i,_h);
    t +=_h;
    if(getSystemFunction())getSystemFunction()->correct(t);
  }
  return t;
}
 Real SingleStepIntegrator::getStepSize(){
   return _h;
 }
 void SingleStepIntegrator::setStepSize(Real h){
    _h=h;
 }
