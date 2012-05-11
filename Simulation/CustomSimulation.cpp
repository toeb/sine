#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>

#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/RungeKutta4.h>
#include <Simulation/Integrators/Implementations/RungeKuttaFehlberg45.h>

#include <Visualization/Renderers/LightRenderer.h>
#include <Visualization/Renderers/CoordinateSystemRenderer.h>
#include <Visualization/Renderers/CameraRenderer.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/Renderers/TextRenderer.h>
#include <Visualization/Renderers/ConnectorRenderer.h>
#include <Visualization/Renderers/ConnectorVelocityRenderer.h>
#include <Visualization/Renderers/ConnectorForceRenderer.h>
#include <Visualization/Renderers/ParticleRenderer.h>
#include <Visualization/Renderers/BoxRenderer.h>
#include <Visualization/Renderers/SpringRenderer.h>

#include <Simulation/SimulationBuilder.h>

#include <map>
#include <sstream>

using namespace IBDS;
using namespace std;

void create4BoxesWithSpring(SimulationBuilder & b, const Vector3D & offset){  
  Box* box1 =b.createBox("box1",offset+Vector3D::Zero(),0);
  Box* box2= b.createBox("box2",offset+Vector3D(0,-1,0),100);
  Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0.2));
  Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));

  box2->addExternalForce(offset+Vector3D(0,0,0),Vector3D(1,0,0));
  b.createSpring("spring1","box1","box2",40,10, box1->getPosition(), box2->getPosition()+Vector3D(0.5,0.5,0.5));
 // b.createSpring("spring2","box2","box3",40,10, box2->getPosition()-Vector3D(0.5,0.5,0.5), box3->getPosition()+Vector3D(0.5,0.5,0.5));
 // b.createSpring("spring3","box3","box4",40,10, box3->getPosition()-Vector3D(0.5,0.5,0.5), box4->getPosition()+Vector3D(0.5,0.5,0.5));
  
}
void createSimplePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
  b.createBox("pendulum",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBallJoint("ball joint 1","fixed point", "pendulum",offset);//create a joint at the particles location

}
void CustomSimulation::buildModel(){ 
  setName(new string("Custom Simulation"));
  

  addRenderer(new LightRenderer());
  addRenderer(new CoordinateSystemRenderer());// renders coordinate system at world origin
  addRenderer(new CameraRenderer());
  
  SimulationBuilder b(*this);  

  b.setGravity(0.3);

  Box* box = b.createBox("test");
  
  box->setAngularVelocity(Vector3D(1,1,1));
  addRenderer(new CoordinateSystemRenderer(box->getPosition(),box->getOrientation()));

  addRenderer(new TextRenderer(*(new string("4 Boxes connected by springs")),*(new  Vector3D(4,1,0))));

  create4BoxesWithSpring(b, Vector3D(6,0,0));

  createSimplePendulum(b,Vector3D(8,0,0));

  
  // loop for adding custom renderers.
  for(auto it = b.getSimulationObjects().begin(); it != b.getSimulationObjects().end(); it++){
    ISimulationObject* obj = (*it).second;
    
  }

  //initialize Integrators.
  Integrator* integrators[3] = {new ExplicitEuler(), new RungeKutta4(0.001), new RungeKuttaFehlberg45()};   
  setIntegrator(integrators[1]);
      
}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  RenderingSimulation::onSimulationObjectAdded(simulationObject);


  Connector * connector = dynamic_cast<Connector*>(simulationObject);
  if(connector){
    addRenderer(new ConnectorRenderer(*connector));
    //addRenderer(new ConnectorVelocityRenderer(*connector));
    //addRenderer(new ConnectorForceRenderer(*connector));
  }

  Particle * particle = dynamic_cast<Particle*>(simulationObject);
  if(particle){
    addRenderer(new ParticleRenderer(*particle));
  }

  Box * box = dynamic_cast<Box*>(simulationObject);
  if(box){
    addRenderer(new BoxRenderer(*box));
  }

  DampedSpring * spring = dynamic_cast<DampedSpring*>(simulationObject);

  if(spring){
    addRenderer(new SpringRenderer(*spring));
  }

}