#include "RungeKutta4.h"

using namespace nspace;


void RungeKutta4::doStep(Real t_i, Real h){ 
  
 /* MatrixOps::multiplyScalar(k1,f(t_i,x,h),h);
  StateMatrix tmp;
  MatrixOps::multiplyScalar(tmp,k1,0.5);
  MatrixOps::add(tmp, tmp,x);
  MatrixOps::multiplyScalar(k2,f(t_i,tmp,h),h);
  MatrixOps::multiplyScalar(tmp,k2,0.5);
  MatrixOps::add(tmp,tmp,x);
  MatrixOps::multiplyScalar(k3,f(t_i,tmp,h),h);
  MatrixOps::add(tmp,x,k3);
  MatrixOps::multiplyScalar(k4,f(t_i,tmp,h),h);
  MatrixOps::multiplyScalar(tmp,k2,2.0);
  MatrixOps::multiplyScalar(k2,k3,2.0);
  MatrixOps::add(tmp,tmp,k1);
  MatrixOps::add(tmp,tmp,k2);
  MatrixOps::add(tmp,tmp,k4);
  MatrixOps::multiplyScalar(tmp,tmp,1/6.0);
  MatrixOps::add(x,x,tmp);*/

  
  k1 =h*f(t_i,x,h);
  k2 = h * f(t_i,x+0.5*k1,h);
  k3 = h * f(t_i,x+0.5*k2,h);
  k4 = h * f(t_i,x+k3,h);
  x = x +(k1+2.0*k2+2.0*k3+k4)/6.0;
  
};



void RungeKutta4::logParameters(std::ostream & o)const{  }
RungeKutta4::RungeKutta4(Real h0):StepIntegrator(h0){
  setName("RungeKutta4");
};
int RungeKutta4::getErrorOrder()const{
  return 4;
}