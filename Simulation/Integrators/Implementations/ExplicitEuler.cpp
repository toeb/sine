#include "ExplicitEuler.h"

using namespace IBDS;

ExplicitEuler::ExplicitEuler(Real h){
  setStepSize(h);
  setName("Explicit Euler");
}

void ExplicitEuler::doStep(const Real & h, VectorND & x_i){
  const VectorND & f_i=f(x_i);
  
  x_i += h*f_i;

}