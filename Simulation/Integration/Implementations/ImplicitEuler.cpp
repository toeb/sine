#include "ImplicitEuler.h"

using namespace std;
using namespace IBDS;

ImplicitEuler::ImplicitEuler(Real stepLength, int maxIterations, Real tolerance ):_tolerance (tolerance),_maxIterations(maxIterations){
  setStepSize(stepLength);
  setName("ImplicitEuler");
}

void ImplicitEuler::doStep(Real t_i,VectorND & x_i, Real h){
  int i=-1;
  Real diff;
  //fix point iteration
  _x_next = x_i;
  while(i < _maxIterations){
    i++;
    _tmp = x_i + h * f(t_i,_x_next,h);
    diff = (_tmp -_x_next).length();
    _x_next = _tmp;
    if(diff < _tolerance)break;    
  }
  x_i = _x_next;
}