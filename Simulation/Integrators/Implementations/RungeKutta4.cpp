#include "RungeKutta4.h"

using namespace IBDS;
using namespace std;
RungeKutta4::RungeKutta4(Real h){
  setStepSize(h);
  setName(new string("Runge Kutta 4"));
}

void RungeKutta4::doStep(const Real & h, VectorND & x_i){
  VectorND k1 = h*f(x_i);
  VectorND k2 = h*f(x_i+0.5*k1);
  VectorND k3 = h*f(x_i+0.5*k2);
  VectorND k4 = h*f(x_i+k3);
  //x_i += 1.0/3.0*(k1+0.5*(k2+k3)+k4);
  x_i += 1.0/6.0*(k1+2*(k2+k3)+k4);
}