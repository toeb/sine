#include "ExplicitEuler.h"

using namespace std;
using namespace IBDS;

ExplicitEuler::ExplicitEuler(Real h){
  setStepSize(h);
  setName("Explicit Euler");
}

void ExplicitEuler::doStep(Real t_i,VectorND & x_i, Real h){
  const VectorND & f_i=f(t_i,x_i,h);
  
  x_i += h*f_i;

}