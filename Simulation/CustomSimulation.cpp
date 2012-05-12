#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>

#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/RungeKutta4.h>
#include <Simulation/Integrators/Implementations/RungeKuttaFehlberg45.h>
#include <Simulation/Integrators/IntegrationAlgorithm.h>

#include <Simulation/Force/ForceAlgorithm.h>

#include <Simulation/ImpulseBasedDynamicsAlgorithm.h>

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
  Box* box2= b.createBox("box2",offset+Vector3D(0,-1,0));
  Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0.2));
  Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));

  box2->addExternalForce(offset+Vector3D(0,0,0),Vector3D(1,0,0));
  b.createSpring("spring1","box1","box2",40,10, box1->getPosition(), box2->getPosition()+Vector3D(0.5,0.5,0.5));
  b.createSpring("spring2","box2","box3",40,10, box2->getPosition()-Vector3D(0.5,0.5,0.5), box3->getPosition()+Vector3D(0.5,0.5,0.5));
  b.createSpring("spring3","box3","box4",40,10, box3->getPosition()-Vector3D(0.5,0.5,0.5), box4->getPosition()+Vector3D(0.5,0.5,0.5));
  
}
void createSimplePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
  b.createBox("pendulum",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBallJoint("ball joint 1","fixed point", "pendulum",offset);//create a joint at the particles location

}
void createDoublePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
 
  b.createBox("leg1",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBox("leg2",offset+Vector3D(l+l/2+0.2,0,0),1,l,0.2,0.2);
  b.createBallJoint("ball joint 1","fixed point", "leg1",offset);//create a joint at the particles location
  b.createBallJoint("ball joint 2","leg1", "leg2",Vector3D(l+0.1,0,0));//create a joint at the particles location

}

void createNPendulum(SimulationBuilder & b, const Vector3D & offset, int n){
  Real l=0.1;
  Box * lastBox=0;
  Box* currentBox=0;
  Vector3D direction(1,-1,0);
  direction.normalize();
  for(int i=0; i < n; i++){
    lastBox = currentBox;
    currentBox = b.createBox();
    if(i==0){
      currentBox->setMass(0);
      continue;
    }
    currentBox->setPosition((l*i)*direction);
    b.createBallJoint("",*(lastBox->getName()),*(currentBox->getName()),(l*i-l/2)*direction);
    if(i==n-1)currentBox->setMass(1); 
  }
}

CustomSimulation::CustomSimulation(){
  addSimulationAlgorithm(new ForceAlgorithm());
  addSimulationAlgorithm(new ImpulseBasedDynamicsAlgorithm());
  addSimulationAlgorithm(new IntegrationAlgorithm(*(new RungeKutta4())));
}

void CustomSimulation::buildModel(){ 
  setName("Custom Simulation");

  addRenderer(new LightRenderer());
  addRenderer(new CoordinateSystemRenderer());// renders coordinate system at world origin
  addRenderer(new CameraRenderer());

  SimulationBuilder b(*this);  

  b.setGravity(9);

 // createDoublePendulum(b,Vector3D::Zero());

  //addRenderer(new TextRenderer(*(new string("4 Boxes connected by springs")),*(new  Vector3D(4,1,0))));

 // create4BoxesWithSpring(b, Vector3D(6,0,0));

 // createSimplePendulum(b,Vector3D(8,0,0));
  createNPendulum(b,Vector3D(13,0,0), 30);
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