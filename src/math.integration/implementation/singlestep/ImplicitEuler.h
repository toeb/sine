#pragma once 

#include <math.integration/SingleStepSolver.h>
namespace nspace{
  namespace math{
    namespace integration{
      
template<typename F, typename X=typename nspace::function_traits<F>::result_type, typename H =typename step_size_type<F>::type, typename T =typename time_type<F>::type>
struct ImplicitEuler :public SingleStepSolver<F,X,H,T>{
  ImplicitEuler(F f):SingleStepSolver(f),_maxIterations(100),_tolerance(0.001){}

  StepCount _maxIterations;
  CoefficientType _tolerance;

  void doStep(){    
    StateType tmp;
    CoefficientType diffSquared;
    //fix point iteration
    auto toleranceSquared = _tolerance*_tolerance;    
    size_t iteration=0;  
    while(iteration < _maxIterations){
      iteration++;
      tmp = x() + h() * f(x(),h(),t());
      diffSquared = nspace::lengthSquared(nspace::subtract(tmp,x()));
      x() = tmp;
      if(diffSquared < toleranceSquared)break;
    }
  }
};
    }
  }
}