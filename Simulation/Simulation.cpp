#include "Simulation.h"

using namespace IBDS;
using namespace std;

Simulation::Simulation():
  //_simulationObjects(*(new vector<ISimulationObject*>())),
  _bodies(*(new vector<Body*>())),
  _integrables(*(new CompositeIntegratable())),
  _forces(*(new vector<Force*>())),
  _integrableConnectors(*(new CompositeIntegratable())),
  _joints(*(new vector<Joint*>())),
  _connectors(*(new vector<Connector*>())),
  _integrator(0),
  _time(0),
  _targetTime(0)
{
}

void Simulation::reset(){
  _bodies.clear();
  _integrables.clear();
  _integrableConnectors.clear();
  _forces.clear();
  _joints.clear();
  _connectors.clear();
  _integrator=0;  
  buildModel();
}


Simulation::~Simulation(){}

void Simulation::addConnector(Connector *c) {
  _connectors.push_back(c);
  _integrableConnectors.addIntegratable(c);
  onSimulationObjectAdded(c);
}

void Simulation::addJoint(Joint *joint) {
  _joints.push_back(joint);
  onSimulationObjectAdded(joint);
  }

void Simulation::addBody(Body * body){
  _bodies.push_back(body);
  //IIntegrable* integrable = dynamic_cast<IIntegrable*>(body);
  _integrables.addIntegratable(body);
  onSimulationObjectAdded(body);
}

void Simulation::addForce(Force *force) {
  _forces.push_back(force);
  onSimulationObjectAdded(force);
}
void Simulation::setIntegrator(Integrator* integrator){
  //if(_integrator)_integrator->setIntegratable(0);
  _integrator = integrator;
  _integrator->setIntegratable(&_integrables);
  
}
Integrator * Simulation::getIntegrator(){
  return _integrator;
}
void Simulation::beforeIntegration(){
  Real targetTime = getTargetTime();
  Real time = getTime();
  // integrate the connectors to be able to approximate their future positions
  _integrator->setIntegratable(&_integrableConnectors);		// temporarily replace the integratable
  _integrator->integrate(time,targetTime);
  // joint position correction
  bool toleranceSatisfied;
  int iterations = 0;
  do {
    toleranceSatisfied = true;
    for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++) {
      bool currentJointSatisfied = (*it)->correctPosition(targetTime - time);
      // if correctPosition returns false for some joint, toleranceSatisfied remains false for the rest of the loop 
      if (toleranceSatisfied) toleranceSatisfied = currentJointSatisfied;
      }
    iterations++;
    } while (!toleranceSatisfied && iterations < 10);	// the loop is repeated until correctPosition returns true for all joints
  _integrator->setIntegratable(&_integrables);
}
void Simulation::afterIntegration(){  
  // joint velocity correction
  for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
    (*it)->correctVelocity();
}

void Simulation::applyExternalForces(){
  // (1) apply custom forces to simulation (subclass controls these)
  applyCustomForces();
  // (2) apply forces added to simulation
  for(vector<Force*>::iterator it = _forces.begin(); it != _forces.end(); it++)
    (*it)->act(_bodies, _time);

}

const Real & Simulation::getTargetTime(){return _targetTime;}
const Real & Simulation::getTime(){return _time;}

bool Simulation::isSimulationValid(){
  if(!getIntegrator()){
    cerr << "No Integrator set"<<endl;
    return false;
  }
  return true;
}

void Simulation::calculateConnectorWorldCoordinateValues(){
  for(auto it = _connectors.begin(); it != _connectors.end(); it++){
    (*it)->calculate();
  }

}

void Simulation::simulate(Real targetTime){
  if(!isSimulationValid()){
    cerr << "INVALID SIMULATION"<<endl;
    return;
  }
  
  // simulation is only allow forwards so this method fails quietly when targetTime < time
  if(targetTime < _time)return;
  _targetTime = targetTime;

  // pre step.  world coordinate values of connectors are calculated only once in every step
  calculateConnectorWorldCoordinateValues();

  // (1) reset all forces
  resetForces();
  // (2) apply external forces
  applyExternalForces();



  // (3) call beforeintegration
  beforeIntegration();

  integrate();
  _time = targetTime;
  afterIntegration();

  
}

void Simulation::integrate(){
  Real targetTime = getTargetTime();
  // main simulation step
  _integrator->integrate(getTime(),targetTime);
  _time=targetTime;
}



void Simulation::resetForces() {
    for(vector<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
    (*it)->resetForce();
}



bool Simulation::initialize(){
  buildModel();
  return isSimulationValid();
}
