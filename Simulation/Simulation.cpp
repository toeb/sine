#include "Simulation.h"
#include "Particle.h"

using namespace IBDS;
using namespace std;


Simulation::Simulation():
  //_simulationObjects(*(new vector<ISimulationObject*>())),
  _bodies(*(new vector<Body*>())),
  _integables(*(new CompositeIntegratable())),
  _forces(*(new vector<Force*>())),
  _integrableConnectors(*(new CompositeIntegratable())),
  _joints(*(new vector<Joint*>())),
  _connectors(*(new vector<Connector*>()))
{

}

Simulation::~Simulation(){}



//void Simulation::addSimulationObject(ISimulationObject * simulationObject){
//  _simulationObjects.push_back(simulationObject);
//  IIntegrable* integrable = dynamic_cast<IIntegrable*>(simulationObject);
//  _integables.addIntegratable(integrable);
//	}
void Simulation::addBody(Body * body){
  _bodies.push_back(body);
  IIntegrable* integrable = dynamic_cast<IIntegrable*>(body);
  _integables.addIntegratable(integrable);
}

void Simulation::addForce(Force *force) {
	_forces.push_back(force);
}

void Simulation::setIntegrator(Integrator* integrator){
  //if(_integrator)_integrator->setIntegratable(0);
  _integrator = integrator;
  _integrator->setIntegratable(&_integables);
}
Integrator * Simulation::getIntegrator(){
  return _integrator;
}

void Simulation::simulate(Real targetTime){
	//if (targetTime > 0.07) exit(0);
  if(targetTime < _time)return;

  /*for(vector<ISimulationObject*>::iterator it = _simulationObjects.begin(); it != _simulationObjects.end(); it++)
	  (*it)->resetForce();*/

  for(vector<Force*>::iterator it = _forces.begin(); it != _forces.end(); it++)
	  (*it)->act(_bodies, _time);

  // integrate the connectors to be able to approximate their future positions
  _integrator->setIntegratable(&_integrableConnectors);		// temporarily replace the integratable
  _integrator->integrate(_time,targetTime);
  // joint position correction
  bool toleranceSatisfied;
  int iterations = 0;
  do {
	  toleranceSatisfied = true;
	  for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++) {
		  bool currentJointSatisfied = (*it)->correctPosition(targetTime - _time);
		  // if correctPosition returns false for some joint, toleranceSatisfied remains false for the rest of the loop 
		  if (toleranceSatisfied) toleranceSatisfied = currentJointSatisfied;
		  }
	  iterations++;
	  } while (!toleranceSatisfied && iterations < 10);	// the loop is repeated until correctPosition returns true for all joints

	// main simulation step
	_integrator->setIntegratable(&_integables);	
	_integrator->integrate(_time,targetTime);
	_time=targetTime;

	// joint velocity correction
	for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
		(*it)->correctVelocity();
}
void Simulation::render(){
	//for (vector<ISimulationObject*>::iterator it = _simulationObjects.begin(); it != _simulationObjects.end(); it++)
	//	(*it)->render();
	for (vector<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
		(*it)->render();

	for (vector<Force*>::iterator it = _forces.begin(); it != _forces.end(); it++)
		(*it)->render();
}

void Simulation::resetForces() {
	  for(vector<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
	  (*it)->resetForce();
	}

void Simulation::addConnector(Connector *c) {
	_connectors.push_back(c);
	_integrableConnectors.addIntegratable(c);
}

void Simulation::addJoint(Joint *joint) {
	_joints.push_back(joint);
	}