#pragma once


namespace nspace{
  namespace math{
    namespace integration{
    

template<typename F, typename X=state_type<F>::type, typename H =step_size_type<F>::type,typename T = time_type<F>::type >
struct SingleStepSolver : public Stepper<F,X,H,T>{
  SingleStepSolver(FunctionType f):Stepper(f){}

};
    }
  }
}