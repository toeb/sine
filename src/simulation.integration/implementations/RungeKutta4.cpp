#include "RungeKutta4.h"

using namespace nspace;
using namespace std;

void RungeKutta4::doStep(StateMatrix & x_next, const StateMatrix & x_i, Real t_i, Real h){
  k1 =h*f(x_i,t_i,h);
  k2 = h * f(x_i+0.5*k1,t_i,h);
  k3 = h * f(x_i+0.5*k2,t_i,h);
  k4 = h * f(x_i+k3,t_i,h);
  x_next = x_i +(k1+2.0*k2+2.0*k3+k4)/6.0;
};

void RungeKutta4::logParameters(std::ostream & o)const{  }
RungeKutta4::RungeKutta4(Real h0):StepIntegrator(h0){
  setName("RungeKutta4");
};
int RungeKutta4::getErrorOrder()const{
  return 4;
}