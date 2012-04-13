#include "ExplicitEuler.h"

using namespace IBDS;

ExplicitEuler::ExplicitEuler(Real h){
  setStepSize(h);
}

void ExplicitEuler::doStep(const Real & h, VectorND & x_i){
  const VectorND & f_i=f(x_i);
  
  x_i += h*f_i;

}