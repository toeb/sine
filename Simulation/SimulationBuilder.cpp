#include "SimulationBuilder.h"
#include <sstream>
using namespace std;
using namespace IBDS;

SimulationBuilder::SimulationBuilder(Simulation & simulation):_simulation(simulation),_connectorNumber(1){}

Box * SimulationBuilder::createBox(string name, const Vector3D & position, Real mass, Real width, Real height, Real depth){
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;    
  Box * box = new Box(mass,width,height,depth);
  box->setName(&name);
  box->setPosition(position);
  addSimulationObject(box);
  return box;
}

Gravity* SimulationBuilder::setGravity(const Vector3D & gravityVector){
  Gravity * gravity = dynamic_cast<Gravity*>(getObject("gravity"));

  if(gravity){
    gravity->setGravity(gravityVector);
    return gravity;
  }
  gravity= new Gravity(gravityVector);
  gravity->setName(new string("gravity"));

  addSimulationObject(gravity);
  return gravity;
}

Gravity* SimulationBuilder::setGravity(Real g){
  return setGravity(Vector3D(0,-g,0));
}
string SimulationBuilder::createUnknownName(){
  stringstream ss;
  ss <<"UnknownObject"<<_unknownCounter++;
  return ss.str();
}
DampedSpring * SimulationBuilder::createSpring( 
  string name, 
  string bodyA,  
  string bodyB, 
  Real k_s,
  Real k_d,
  const Vector3D & r_a_wcs, 
  const Vector3D & r_b_wcs,
  Real neutralLength)
{
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;    
  //create connectors
  Connector * a = createConnector(bodyA,r_a_wcs,name);
  Connector * b = createConnector(bodyB,r_b_wcs,name);
  // if a connector could not be created return  
  if(!(a&&b))return 0;
  //calculate current distance between connectors
  if(neutralLength<0)neutralLength = (r_a_wcs - r_b_wcs).length();
  //create spring
  DampedSpring * spring = new DampedSpring(*a,*b,k_s,k_d,neutralLength);
  spring->setName(&name);
  //add objects
  addSimulationObject(a);
  addSimulationObject(b);
  addSimulationObject(spring);

  return spring;
}

//Sphere * SimulationBuilder::createSphere(string name, const Vector3D & position, Real mass,Real radius){}

Particle * SimulationBuilder::createParticle(string name, const Vector3D & position, Real mass){  
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;
  Particle * particle = new Particle();
  particle->setName(new string(name));
  particle->setPosition(position);
  particle->setMass(mass);
  addSimulationObject(particle);
}

BallJoint * SimulationBuilder::createBallJoint(string jointName, string bodyA, string bodyB, const Vector3D & position){
  
  if(jointName.compare("")==0)jointName = createUnknownName();
  if(nameExists(jointName))return 0;
  //create connectors
  Connector * a = createConnector(bodyA,position);
  Connector * b = createConnector(bodyB,position);
  //return if a connector was not correctly created
  if(!(a&&b))return 0;
  //create ball joint
  BallJoint * ballJoint = new BallJoint(*a,*b);
  ballJoint->setName(&jointName);
  
  //add simulation objects
  addSimulationObject(a);
  addSimulationObject(b);
  addSimulationObject(ballJoint);
  
  return ballJoint;
}

string * SimulationBuilder::createConnectorName(string a, string b){
  stringstream ss;
  ss << "connector"<<(_connectorNumber++)<<": "<<a<< " <-> " <<b;
  return new string(ss.str());
}

Connector* SimulationBuilder::createConnector(string bodyName, const Vector3D & position, string connectsTo){
  Body * body = dynamic_cast<Body*>(getObject(bodyName));
  if(!body)return 0;
  Connector * connector = createRigidBodyConnector(body,position);
  if(!connector){
   connector = createParticleConnector(body,position);
  }
  if(!connector)return 0;
  connector->setName(createConnectorName(bodyName,connectsTo));
  return connector;
}

ParticleConnector * SimulationBuilder::createParticleConnector(Body* body, const Vector3D & position){
  Particle * particle = dynamic_cast<Particle*>(body);
  if(!particle)return 0;
  if(position!=particle->getPosition())return 0; //particle connectors may only be connected at the position of the particle
  
  ParticleConnector* connector = new ParticleConnector(*particle);
  return connector;
}
std::map<std::string,ISimulationObject *> & SimulationBuilder::getSimulationObjects(){
  return _simulationObjects;
}

RigidBodyConnector * SimulationBuilder::createRigidBodyConnector(Body* body, const Vector3D &position){
  RigidBody* rigidBody = dynamic_cast<RigidBody*>(body);
  if(!rigidBody)return 0;    
  RigidBodyConnector * result = RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,position);
  return result;
}

ISimulationObject* SimulationBuilder::getObject(string name){
  if(!nameExists(name))return 0;
  return _simulationObjects[name];
}

bool SimulationBuilder::nameExists(string name){
  return nameExists(&name);
}

bool SimulationBuilder::nameExists(const string * name){
  if(!name)return false;
  if(_simulationObjects.find(*name) == _simulationObjects.end()){
    return false;
  }
  return true;
}

bool SimulationBuilder::addSimulationObject(ISimulationObject * obj){
  if(!obj->getName())return false;
  if(nameExists(*(obj->getName())))return false;
  _simulationObjects[*(obj->getName())] = obj;

  if(dynamic_cast<Body*>(obj)){
    _simulation.addBody(dynamic_cast<Body*>(obj));
  }
  if(dynamic_cast<Force*>(obj)){
    _simulation.addForce(dynamic_cast<Force*>(obj));
  }
  if(dynamic_cast<Connector*>(obj)){
    _simulation.addConnector(dynamic_cast<Connector*>(obj));
  }
  if(dynamic_cast<Joint*>(obj)){
    _simulation.addJoint(dynamic_cast<Joint*>(obj));
  }

  return true;
}
