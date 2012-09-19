#include "StepIntegrator.h"
using namespace nspace;

void StepIntegrator::integrate(Real  a, Real b){
  setLowerBound(a);
  setUpperBound(b);
  _t=a;
  while(needsIntegration()){   
    //std::cout << f(_t,x(),0.1) << std::endl;
    step();
  }
}