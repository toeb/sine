#pragma once 

#include <math.integration/SingleStepSolver.h>
namespace nspace{
  namespace math{
    namespace integration{
      

template<typename F, typename X=typename nspace::function_traits<F>::result_type, typename H =typename step_size_type<F>::type, typename T = typename time_type<F>::type>
struct ExplicitEuler :public SingleStepSolver<F,X,H,T>{
  ExplicitEuler(F f):SingleStepSolver(f){}
  void doStep(){    
    x()=x()+h()*f(x(),h(),t());
  }
};

    }
  }
}