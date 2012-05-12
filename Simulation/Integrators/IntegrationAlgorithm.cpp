#include "IntegrationAlgorithm.h"

using namespace IBDS;

IntegrationAlgorithm::IntegrationAlgorithm(Integrator & integrator):_integrator(integrator){
  _integrator.setIntegratable(&_integrables);
  setName(*(integrator.getName()));
}

bool IntegrationAlgorithm::isCompatibleWith(ISimulationAlgorithm * algorithm){
  if(dynamic_cast<IntegrationAlgorithm*>(algorithm))return false;
  return true;
}
bool IntegrationAlgorithm::addSimulationObject(ISimulationObject * object){
  IIntegrable * integrable =dynamic_cast<IIntegrable*>(object);
  if(!integrable)return false;
  _integrables.addIntegratable(integrable);
  _integrator.setIntegratable(&_integrables);
}
void IntegrationAlgorithm::reset(){
  _integrables.clear();
}
void IntegrationAlgorithm::integrationStep(Real time, Real h){
  _integrator.integrate(time,time+h);
}