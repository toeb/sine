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
using namespace IBDS;


void CustomSimulation::buildModel(){
  setSimulationName("Custom Simulation");

  
    //initialize Integrators.
    Integrator* integrators[3] = {new ExplicitEuler(), new RungeKutta4(0.001), new RungeKuttaFehlberg45()};    
  //  _integratorManager = new IntegratorsManager(this,integrators,3);
//    MiniGL::setIntegratorsManager(_integratorManager);

    setIntegrator(integrators[1]);

  addRenderer(new LightRenderer());
  addRenderer(new CoordinateSystemRenderer());
  addRenderer(new CameraRenderer());
  addRenderer(new TweakBarRenderer());

  Box * cube = new Box(0,1,1,1);
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
  
  Connector *c1 = new RigidBodyConnector(cube,new Vector3D(0,0,0));
  Connector *c2 = new RigidBodyConnector(cube2,new Vector3D(0,0,0));
  Connector *c3 = new RigidBodyConnector(cube2,new Vector3D(0,-0.5,0));
  Connector *c4 = new RigidBodyConnector(cube3,new Vector3D(0,0.5,0));
  Connector *c5 = new ParticleConnector(swingHolder1);
  Connector *c6 = new ParticleConnector(swingHolder2);
  Connector *c7 = new RigidBodyConnector(swingSegment1,new Vector3D(swingHolder1->getPosition() - swingSegment1->getPosition()));
  Connector *c8 = new RigidBodyConnector(swingSegment2,new Vector3D(swingHolder2->getPosition() - swingSegment2->getPosition()));
  Vector3D swingBottomLeft(swingSegment3->getPosition()[0]-swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
  Vector3D swingBottomRight(swingSegment3->getPosition()[0]+swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
  Connector *c9 = new RigidBodyConnector(swingSegment1,new Vector3D(swingBottomLeft - swingSegment1->getPosition()));
  Connector *c10 = new RigidBodyConnector(swingSegment3,new Vector3D(swingBottomLeft - swingSegment3->getPosition()));
  Connector *c11 = new RigidBodyConnector(swingSegment3,new Vector3D(swingBottomRight - swingSegment3->getPosition()));
  Connector *c12 = new RigidBodyConnector(swingSegment2,new Vector3D(swingBottomRight - swingSegment2->getPosition()));
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


  }/**/