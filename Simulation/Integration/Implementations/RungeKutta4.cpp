#include "RungeKutta4.h"

using namespace IBDS;
using namespace std;
RungeKutta4::RungeKutta4(Real h){
  setStepSize(h);
  setName("Runge Kutta 4");
}

void RungeKutta4::doStep(Real t_i,VectorND & x_i, Real h){
  VectorND k1 = h*f(t_i,x_i,h);
  VectorND k2 = h*f(t_i+0.5*h,x_i+0.5*k1,0.5*h);
  VectorND k3 = h*f(t_i+0.5*h,x_i+0.5*k2,0.5*h);
  VectorND k4 = h*f(t_i+h,x_i+k3,0.5*h);
  //x_i += 1.0/3.0*(k1+0.5*(k2+k3)+k4);
  x_i += 1.0/6.0*(k1+2*(k2+k3)+k4);
}