#include "Integrator.h"
using namespace nspace;
using namespace std;




Integrator::Integrator():_evaluator(0){
  setName("Integrator");
}

void Integrator::setEvaluator(Evaluator * evaluator){
  _evaluator = evaluator;
}