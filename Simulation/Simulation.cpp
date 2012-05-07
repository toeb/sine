#include "Simulation.h"

using namespace IBDS;
using namespace std;

Simulation::Simulation():
  //_simulationObjects(*(new vector<ISimulationObject*>())),
  _bodies(*(new vector<Body*>())),
  _integables(*(new CompositeIntegratable())),
  _forces(*(new vector<Force*>())),
  _integrableConnectors(*(new CompositeIntegratable())),
  _joints(*(new vector<Joint*>())),
  _connectors(*(new vector<Connector*>())),
  _renderObjects(*(new vector<ISimulationObject*>)),
  _integrator(0)
{

}

Simulation::~Simulation(){}


void Simulation::addBody(Body * body){
  _bodies.push_back(body);
  //IIntegrable* integrable = dynamic_cast<IIntegrable*>(body);
  _integables.addIntegratable(body);
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

void Simulation::simulate(Real targetTime){
  if(!isSimulationValid()){
    cerr << "INVALID SIMULATION"<<endl;
    return;
  }

  // simulation is only allow forwards so this method fails quietly when targetTime < time
  if(targetTime < _time)return;

  _targetTime = targetTime;
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
  _integrator->setIntegratable(&_integables);	
  _integrator->integrate(getTime(),targetTime);
  _time=targetTime;
}

void Simulation::render(){
  updateRenderList(_renderObjects);
  for(auto it = _renderObjects.begin(); it!= _renderObjects.end(); it++){
    (**it).render();
}

  //for (vector<ISimulationObject*>::iterator it = _simulationObjects.begin(); it != _simulationObjects.end(); it++)
  //	(*it)->render();
  /*for (vector<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
    (*it)->render();

  for (vector<Force*>::iterator it = _forces.begin(); it != _forces.end(); it++)
    (*it)->render();*/
}
void Simulation::initializeRenderList(vector<ISimulationObject*> & renderObjects){
  for (auto it = _bodies.begin(); it != _bodies.end(); it++)
    renderObjects.push_back(*it);

  for (auto it = _forces.begin(); it != _forces.end(); it++)
    renderObjects.push_back(*it);
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

void Simulation::initializeRenderer(){
 

 /* MiniGL::init (argc, argv, 800, 600, 0, 0, getSimulationName());

  MiniGL::initLights ();
  MiniGL::setClientIdleFunc (50, timeStep);				

  buildModel ();

  MiniGL::setClientSceneFunc(render);			
  MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));*/
}

void Simulation::initialize(){
  initializeSimulation();
  buildModel();
  initializeRenderer();
}

const char* Simulation::getSimulationName()const{
  return _simulationName;
}
void Simulation::setSimulationName(const char* name){
  _simulationName = name;
}


void Simulation::setCommandLineArguments(int argc, char** argv){
  _commandlineArgumentArray  = argv;
  _commandlineArgumentCount = argc;
}
void Simulation::getCommandLineArguments(int & argc, char** argv)const{
  argc = _commandlineArgumentCount;
  argv = _commandlineArgumentArray;
}