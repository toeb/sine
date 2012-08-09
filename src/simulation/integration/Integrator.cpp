#include "Integrator.h"
using namespace nspace;
using namespace std;





void Integrator::integrate(Real a, Real b){
  tick();  
  State state(x);
  _statefulObject->exportState(state);
  doIntegration(a,b);
  _statefulObject->importState(state); 
  tock();
}

const StateMatrix& Integrator::f(Real t, const StateMatrix & x, Real h){
  
  _statefulObject->importState(State(x));
	//cout << State(x)<<endl;
  if(_systemFunction)_systemFunction->evaluate(t,h);
 // StateMatrix xDot;
	State state(_derivedState);
  if(!x.size())return _derivedState;
	_statefulObject->resizeState(state);
	_derivedState.setZero();
  _statefulObject->exportDerivedState(state);
  _evaluationCount++;
  return _derivedState;
}



Integrator::Integrator():_systemFunction(0), _statefulObject(0),_evaluationCount(0),_log(0),_dimension(0){
  setName("Integrator");
}

long Integrator::getEvaluationCount()const{return _evaluationCount;}
void Integrator::resetEvaluationCount(){_evaluationCount=0;}

void Integrator::logIntegratorInfo(std::ostream & o)const{
  o<<"<integratorInfo>\n";
  o<<"  <name>"<<this->getName()<<"</name>\n";
  o<<"  <order>"<<this->getErrorOrder()<<"</order>\n";
  o<<"  <parameters>\n";
  this->logParameters(o);
  o<<"  </parameters>\n";
  o<<"</integratorInfo>\n";
};

void Integrator::setStatefulObject(IStatefulObject * integrable){
  _statefulObject = integrable;
}
IStatefulObject *  Integrator::statefulObject(){
  return _statefulObject;
}
void Integrator::setSystemFunction(ISystemFunction  * function){
  _systemFunction = function;
}
ISystemFunction * Integrator::getSystemFunction(){
  return _systemFunction;
}

