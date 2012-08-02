#include "RungeKutta4.h"

using namespace nspace;


void RungeKutta4::doStep(Real t_i, Real h){ 
  k1 = h * f(t_i,x,h);
  k2 = h * f(t_i,x+0.5*k1,h);
  k3 = h * f(t_i,x+0.5*k2,h);
  k4 = h * f(t_i,x+k3,h);
  x = x +(k1+2*k2+2*k3+k4)/6;

};



void RungeKutta4::logParameters(std::ostream & o)const{  }
RungeKutta4::RungeKutta4(Real h0):StepIntegrator(h0){
  setName("RungeKutta4");
};
int RungeKutta4::getErrorOrder()const{
  return 4;
}