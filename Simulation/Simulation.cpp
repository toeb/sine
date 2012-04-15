#include "Simulation.h"
#include "Particle.h"

using namespace IBDS;
using namespace std;


Simulation::Simulation():
  _simulationObjects(*(new vector<ISimulationObject*>())),
  _integables(*(new CompositeIntegratable()))
{

}

Simulation::~Simulation(){}



void Simulation::addSimulationObject(ISimulationObject * simulationObject){
  _simulationObjects.push_back(simulationObject);
  IIntegrable* integrable = dynamic_cast<IIntegrable*>(simulationObject);
  _integables.addIntegratable(integrable);
    
}
void Simulation::setIntegrator(Integrator* integrator){
  if(_integrator)_integrator->setIntegratable(0);
  _integrator = integrator;
  _integrator->setIntegratable(&_integables);
}
Integrator * Simulation::getIntegrator(){
  return _integrator;
}

void Simulation::simulate(Real targetTime){
  if(targetTime < _time)return;
  _integrator->integrate(_time,targetTime);
  _time=targetTime;
}
void Simulation::render(){

}
