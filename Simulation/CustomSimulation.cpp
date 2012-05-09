#include "CustomSimulation.h"

#include <Simulation/SimulationObjects/Box.h>
#include <Simulation/SimulationObjects/Sphere.h>
#include <Simulation/SimulationObjects/Particle.h>
#include <Simulation/SimulationObjects/DampedSpring.h>
#include <Simulation/SimulationObjects/RigidBodyConnector.h>
#include <Simulation/SimulationObjects/BallJoint.h>
#include <Simulation/SimulationObjects/Gravity.h>
#include <Simulation/SimulationObjects/ParticleConnector.h>
#include <Visualization/IRenderer.h>

#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/RungeKutta4.h>
#include <Simulation/Integrators/Implementations/RungeKuttaFehlberg45.h>

#include <Visualization/Renderers/LightRenderer.h>
#include <Visualization/Renderers/CoordinateSystemRenderer.h>
#include <Visualization/Renderers/CameraRenderer.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/Renderers/TweakBarRenderer.h>

#include <map>
#include <sstream>

using namespace IBDS;
using namespace std;



class SimulationBuilder{
private:
  Simulation & _simulation;
  map<string,ISimulationObject *> _simulationObjects; 
public:
  SimulationBuilder(Simulation & simulation):_simulation(simulation),_connectorNumber(1){}
  Box * createBox(string name, const Vector3D & position=Vector3D::Zero(), Real mass=1, Real width=1, Real height=1, Real depth=1){
    if(nameExists(name))return 0;
    Box * box = new Box(mass,width,height,depth);
    box->setName(&name);
    box->setPosition(position);
    addSimulationObject(box);
    return box;
  }
  Gravity* setGravity(const Vector3D & gravityVector){
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
  Gravity* setGravity(Real g){
    return setGravity(Vector3D(0,-g,0));
  }

  DampedSpring * createSpring(
    string name, 
    string bodyA, 
    string bodyB, 
    Real k_s,
    Real k_d,
    const Vector3D & r_a_wcs, 
    const Vector3D & r_b_wcs,
    Real neutralLength = -1)
  {
    if(nameExists(name))return 0;    
    //create connectors
    Connector * a = createConnector(bodyA,r_a_wcs,name);
    Connector * b = createConnector(bodyB,r_b_wcs,name);
    // if a connector could not be created return  
    if(!(a&&b))return 0;
    //calculate current distance between connectors
    if(neutralLength<0)neutralLength = (r_a_wcs - r_b_wcs).length();
    //create spring
    DampedSpring * spring = new DampedSpring(a,b,k_s,k_d,neutralLength);
    spring->setName(&name);
    //add objects
    addSimulationObject(a);
    addSimulationObject(b);
    addSimulationObject(spring);

    return spring;
  }

  Sphere * createSphere(string name, const Vector3D & position=Vector3D::Zero(), Real mass=1,Real radius = 1){}
  Particle * createParticle(string name, const Vector3D & position=Vector3D::Zero(), Real mass=1){
    if(nameExists(name))return 0;
    Particle * particle = new Particle();
    particle->setName(new string(name));
    particle->setPosition(position);
    particle->setMass(mass);
    addSimulationObject(particle);
  }
  BallJoint * createBallJoint(string jointName, string bodyA, string bodyB, const Vector3D & position){
    if(nameExists(jointName))return 0;
    
    Connector * a = createConnector(bodyA,position);
    Connector * b = createConnector(bodyB,position);
    
    if(!(a&&b))return 0;

    BallJoint * ballJoint = new BallJoint(a,b);
    ballJoint->setName(&jointName);
  
    addSimulationObject(a);
    addSimulationObject(b);
    addSimulationObject(ballJoint);

    return ballJoint;
  }

private:
  int _connectorNumber;
  string * createConnectorName(string a, string b){
    stringstream ss;
    ss << "connector"<<(_connectorNumber++)<<": "<<a<< " <-> " <<b;
    return new string(ss.str());
  }
  Connector* createConnector(string bodyName, const Vector3D & position, string connectsTo="Unknown"){
    Body * body = dynamic_cast<Body*>(getObject(bodyName));
    if(!body)return 0;
    Connector * connector = createRigidBodyConnector(body,position);
    connector->setName(createConnectorName(bodyName,connectsTo));
    if(connector)return connector;
    connector = createParticleConnector(body,position);
    return connector;
  }
  ParticleConnector * createParticleConnector(Body* body, const Vector3D & position){
    Particle * particle = dynamic_cast<Particle*>(body);
    if(!particle)return 0;
  }
  RigidBodyConnector * createRigidBodyConnector(Body* body, const Vector3D &position){
    RigidBody* rigidBody = dynamic_cast<RigidBody*>(body);
    if(!rigidBody)return 0;    
    RigidBodyConnector * result = RigidBodyConnector::createWithWorldConnectionPoint(*rigidBody,position);
    return result;
  }
  ISimulationObject* getObject(string name){
    if(!nameExists(name))return 0;
    return _simulationObjects[name];
  }
  bool nameExists(string name){
    return nameExists(&name);
  }
  bool nameExists(const string * name){
    if(!name)return false;
     if(_simulationObjects.find(*name) == _simulationObjects.end()){
      return false;
    }
     return true;
  }
  bool addSimulationObject(ISimulationObject * obj){
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
    return true;
  }
  
};

void create4BoxesWithSpring(SimulationBuilder & b, const Vector3D & offset){  
  Box* box1 =b.createBox("box1",offset+Vector3D::Zero(),0);
  Box* box2= b.createBox("box2",offset+Vector3D(0,-1,0));
  Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0));
  Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));
  
  b.setGravity(9.81);
  b.createSpring("spring1","box1","box2",60.0,1, box1->getPosition(), box2->getPosition());
  b.createSpring("spring2","box2","box3",60.0,1, box2->getPosition(), box3->getPosition());
  b.createSpring("spring3","box3","box4",60.0,1, box3->getPosition(), box4->getPosition());
  
}
void createSimplePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
  b.createBox("pendulum",offset+Vector3D(l/2,0,0),1,l,0.2,0.2);
}
void CustomSimulation::buildModel(){
 
  setName(new string("Custom Simulation"));
  //initialize Integrators.
  Integrator* integrators[3] = {new ExplicitEuler(), new RungeKutta4(0.001), new RungeKuttaFehlberg45()};    
  //_integratorManager = new IntegratorsManager(this,integrators,3);
  //MiniGL::setIntegratorsManager(_integratorManager);

  setIntegrator(integrators[1]);

  addRenderer(new LightRenderer());
  addRenderer(new CoordinateSystemRenderer());
  addRenderer(new CameraRenderer());
  addRenderer(new TweakBarRenderer());
  
  SimulationBuilder b(*this);

  create4BoxesWithSpring(b, Vector3D(6,0,0));

  createSimplePendulum(b,Vector3D(8,0,0));
  /* Box * cube = new Box(0,1,1,1);
  Box * cube2 = new Box(1,1,1,1);
  Box * cube3 = new Box(1,1,1,1);
  Sphere * sphere = new Sphere(1,0.5);
  Box * plank = new Box(0.5,3,0.5,1);

  double swingThickness = 0.03;
  double swingHeight = 4.5;
  double swingWidth = 1.5;
  RigidBody* swingSegment1 = new Box(1,swingThickness,swingHeight,swingThickness);	//left
  RigidBody* swingSegment2 = new Box(1,swingThickness,swingHeight,swingThickness);	// right
  RigidBody* swingSegment3 = new Box(0.5,swingWidth,swingThickness,swingThickness);	// seat
  Particle* swingHolder1 = new Particle();
  Particle* swingHolder2 = new Particle();
  
  cube->setPosition(Vector3D(2,2,2));
  cube2->setPosition(Vector3D(0,0,0));
  cube3->setPosition(cube2->getPosition() + Vector3D(0,-2,0));
  sphere->setPosition(Vector3D(1,1,0));
  plank->setPosition(Vector3D(3,-2,0));

  Vector3D swingOrigin(4,1,0);
  Quaternion q;
  double swingAngle = 8.0 * 3.14159265358979323846 / 180;
  q.setFromAxisAngle(Vector3D(1,0,0),-swingAngle);
  swingSegment1->setOrientation(q);
  swingSegment2->setOrientation(q);
  swingSegment1->setPosition(swingOrigin + Vector3D(-swingWidth/2,0,0));
  swingSegment2->setPosition(swingOrigin + Vector3D( swingWidth/2,0,0));
  swingSegment3->setPosition(swingOrigin + Vector3D(0,-cos(swingAngle) * swingHeight / 2,sin(swingAngle) * swingHeight / 2));
  swingHolder1->setPosition(swingOrigin + Vector3D(-swingWidth/2,cos(swingAngle)*swingHeight/2,-sin(swingAngle)*swingHeight / 2));
  swingHolder2->setPosition(swingOrigin + Vector3D( swingWidth/2,cos(swingAngle)*swingHeight/2,-sin(swingAngle)*swingHeight / 2));

  swingHolder1->setMass(0);
  swingHolder2->setMass(0);
  //for(int i=0 ;i <5; i++){
  //  Particle* p = new Particle();
  //  p->addExternalForce(Vector3D((rand()%100-50)*0.01,(rand()%100-50)*0.01,(rand()%100-50)*0.01));
  //  particles.push_back(p);
  //  simulation.addBody(p);
  //}

  addBody(cube);
  addBody(cube2);
  addBody(cube3);
  addBody(sphere);
  addBody(plank);
  
  addBody(swingSegment1);
  addBody(swingSegment2);
  addBody(swingSegment3);
  addBody(swingHolder1);
  addBody(swingHolder2);

  // Create damped springs
  // spring parameters
  Real restLength = 1.5;
  Real ks = 60;
  Real kd = 0;

  Real restLength2 = 1.5;
  Real ks2 = 40;
  Real kd2 = 1;

  DampedSpring *spring1, *spring2;
  /*
  Connector *c1 = RigidBodyConnector::createWithLocalConnectionPoint(*cube, Vector3D(0,0,0));
  Connector *c2 = RigidBodyConnector::createWithLocalConnectionPoint(*cube2, Vector3D(0,0,0));
  Connector *c3 = RigidBodyConnector::createWithLocalConnectionPoint(*cube2, Vector3D(0,-0.5,0));
  Connector *c4 = RigidBodyConnector::createWithLocalConnectionPoint(*cube3, Vector3D(0,0.5,0));
  Connector *c5 = new ParticleConnector(swingHolder1);
  Connector *c6 = new ParticleConnector(swingHolder2);
  Connector *c7 = RigidBodyConnector::createWithWorldConnectionPoint(*swingSegment1, swingHolder1->getPosition());
  Connector *c8 = new RigidBodyConnector(*swingSegment2, Vector3D(swingHolder2->getPosition() - swingSegment2->getPosition()));
  Vector3D swingBottomLeft(swingSegment3->getPosition()[0]-swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
  Vector3D swingBottomRight(swingSegment3->getPosition()[0]+swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
  Connector *c9 = new RigidBodyConnector(*swingSegment1, Vector3D(swingBottomLeft - swingSegment1->getPosition()));
  Connector *c10 = new RigidBodyConnector(*swingSegment3, Vector3D(swingBottomLeft - swingSegment3->getPosition()));
  Connector *c11 = new RigidBodyConnector(*swingSegment3, Vector3D(swingBottomRight - swingSegment3->getPosition()));
  Connector *c12 = new RigidBodyConnector(*swingSegment2, Vector3D(swingBottomRight - swingSegment2->getPosition()));
  addConnector(c1);
  addConnector(c2);
  addConnector(c3);
  addConnector(c4);
  addConnector(c5);
  addConnector(c6);
  addConnector(c7);
  addConnector(c8);

  spring1 = new DampedSpring(c1,c2,ks,kd,restLength);
  spring2 = new DampedSpring(c3,c4,ks2,kd2,restLength2);

  addForce(spring1);
  addForce(spring2);
  addForce(new Gravity());

  addJoint(new BallJoint(c5,c7));
  addJoint(new BallJoint(c6,c8));
  addJoint(new BallJoint(c9,c10));
  */
  }/**/