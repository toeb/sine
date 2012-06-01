#include "SimulationBuilder.h"
#include <sstream>
using namespace std;
using namespace IBDS;

SimulationBuilder::SimulationBuilder(Simulation & simulation):_simulation(simulation),_connectorNumber(1),_unknownCounter(1){}


Rectangle * SimulationBuilder::createFixedRectangle(std::string name,const Vector3D& position,const Quaternion & orientation,Real width,Real height){
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;  
  Rectangle * rectangle = new Rectangle(Vector2D(width,height));
  rectangle->setOrientation(orientation);
  rectangle->setPosition(position+_currentOffset);
  rectangle->setName(name);
  addSimulationObject(rectangle);
  return rectangle;
}


DynamicBox * SimulationBuilder::createBox(string name, const Vector3D & position, Real mass, Real width, Real height, Real depth){
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;    
  DynamicBox * box = new DynamicBox(mass,width,height,depth);
  box->setName(name);
  box->setPosition(position+_currentOffset);
  addSimulationObject(box);
  return box;
}

Sphere * SimulationBuilder::createSphere(std::string name, const Vector3D & position, Real mass,Real radius){
  if(name.compare("")==0)name = createUnknownName();
  if(nameExists(name))return 0;    
  DynamicSphere * sphere = new DynamicSphere(mass,radius);
  sphere->setName(name);
  sphere->setPosition(position+_currentOffset);
  addSimulationObject(sphere);
  return sphere;
}
Gravity* SimulationBuilder::setGravity(const Vector3D & gravityVector){
  Gravity * gravity = dynamic_cast<Gravity*>(getObject("gravity"));

  if(gravity){
    gravity->setGravity(gravityVector);
    return gravity;
  }
  gravity= new Gravity(gravityVector);
  gravity->setName("gravity");

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
  spring->setName(name);
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
  particle->setName(name);
  particle->setPosition(position+_currentOffset);
  particle->setMass(mass);
  addSimulationObject(particle);
}

BallJoint * SimulationBuilder::createBallJoint(string jointName, string bodyA, string bodyB, const Vector3D & position){
  
  if(jointName.compare("")==0)jointName = createUnknownName();
  if(nameExists(jointName))return 0;
  //create connectors
  Connector * a = createConnector(bodyA,position+_currentOffset);
  Connector * b = createConnector(bodyB,position+_currentOffset);
  //return if a connector was not correctly created
  if(!(a&&b))return 0;
  //create ball joint
  BallJoint * ballJoint = new BallJoint(*a,*b);
  ballJoint->setName(jointName);
  
  //add simulation objects
  addSimulationObject(a);
  addSimulationObject(b);
  addSimulationObject(ballJoint);
  
  return ballJoint;
}

string  SimulationBuilder::createConnectorName(string a, string b){
  stringstream ss;
  ss << "connector"<<(_connectorNumber++)<<": "<<a<< " <-> " <<b;
  return ss.str();
}

Connector* SimulationBuilder::createConnector(string bodyName, const Vector3D & position, string connectsTo){
  DynamicBody * body = dynamic_cast<DynamicBody*>(getObject(bodyName));
  if(!body)return 0;
  Connector * connector = createRigidBodyConnector(body,position);
  if(!connector){
   connector = createParticleConnector(body,position);
  }
  if(!connector)return 0;
  connector->setName(createConnectorName(bodyName,connectsTo));
  return connector;
}

ParticleConnector * SimulationBuilder::createParticleConnector(DynamicBody* body, const Vector3D & position){
  Particle * particle = dynamic_cast<Particle*>(body);
  if(!particle)return 0;
 
  ParticleConnector* connector = new ParticleConnector(*particle);
  return connector;
}
std::map<std::string,ISimulationObject *> & SimulationBuilder::getSimulationObjects(){
  return _simulationObjects;
}

RigidBodyConnector * SimulationBuilder::createRigidBodyConnector(DynamicBody* body, const Vector3D &position){
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
_simulation.addSimulationObject(obj);

  return true;
}
