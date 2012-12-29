#include "StepIntegrator.h"
using namespace nspace;

StepIntegrator::StepIntegrator(Real h0):
  _LowerBound(-REAL_MAX),
  _UpperBound(REAL_MAX),
  _Time(0.0),
  _CurrentStepSize(h0),
  _InitialStepSize(h0){
}
void StepIntegrator::integrate(Real  a, Real b){
  setLowerBound(a);
  setUpperBound(b);
  setTime(a);
  while(needsIntegration()){
    //std::cout << f(_t,x(),0.1) << std::endl;
    step();
  }
}

Time StepIntegrator::step(){
  Evaluator * evaluator = getEvaluator();
  if(!evaluator){
    logError("trying to perform step, even though no evaluator is set");
  }
  Time t = getTime();
  Time h = getCurrentStepSize();
  if(!needsIntegration())return t;

  const StateMatrix & x = evaluator->x();

  if(x.size()){
    x_next.resize(x.rows(),x.cols());
    x_next.setZero();
    doStep(x_next, evaluator->x(),t,h);
    evaluator->setX(x_next);
  }
  t += h;
  setTime(t);
  return t;
}

Time StepIntegrator::integrate(){
  while(needsIntegration())step();
  return getTime();
}

bool StepIntegrator::needsIntegration()const{
  // if the integrator has reached not reached the upper bound
  return _Time+_CurrentStepSize < _UpperBound;
}

void StepIntegrator::propertyChanging(Time, LowerBound){
  if(_Time < newvalue) _Time=newvalue;
  if(_LowerBound > _UpperBound){
    logWarning("StepIntegrator::setLowerBound: attempt was made to set lower bound higher than upper bound ");
    newvalue= _UpperBound;
  }
}
void StepIntegrator::propertyChanging(Time, UpperBound){
  if(_Time > newvalue) setTime(newvalue);
  if(newvalue < _LowerBound){
    logWarning("StepIntegrator::setLowerBound: attempt was made to set upper bound lower than lower bound");
    newvalue = _LowerBound;
  }
}