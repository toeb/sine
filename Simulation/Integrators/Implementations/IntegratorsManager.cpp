#include "IntegratorsManager.h"
using namespace IBDS;

IntegratorsManager::IntegratorsManager() : _simulation(0), _integrators(0){
}

IntegratorsManager::~IntegratorsManager(){
}

IntegratorsManager::IntegratorsManager(Simulation * const simulation, Integrator* const * const integrators, int integratorsCount) :
	_simulation(simulation),_integrators(integrators),_integratorsCount(integratorsCount){
	_integratorNames = new std::string[integratorsCount];
	for (int i = 0; i < integratorsCount; i++)
		_integratorNames[i] = integrators[i]->getName();
}

std::string const * IntegratorsManager::getIntegratorNames(){
	return _integratorNames;
}

int IntegratorsManager::getIntegratorsCount() {
	return _integratorsCount;
}

void IntegratorsManager::setIntegrator (std::string const & integratorName){
	for (int i = 0; i < _integratorsCount; i++) {
		if (_integratorNames[i].compare(integratorName) == 0) {
			_simulation->setIntegrator(_integrators[i]);
			return;
		}
	}
}

std::string const & IntegratorsManager::getIntegrator(){
	return (_simulation->getIntegrator())->getName();
}