#include "SingleStepIntegrator.h"

using namespace IBDS;


 void SingleStepIntegrator::doIntegration(const VectorND& x_0, VectorND& x_i, const Real & a, const Real & b){
  Real t = a;
  x_i = x_0;
  while(t+_h < b){
    doStep(_h,x_i);
    t +=_h;
  }
  // the last step length is smaller than h.  it is the difference between interval end
  // b and currentTime
  Real h_rest = b-t;
  doStep(h_rest,x_i);
}
 Real SingleStepIntegrator::getStepSize(){
   return _h;
 }
 void SingleStepIntegrator::setStepSize(Real h){
    _h=h;
 }
