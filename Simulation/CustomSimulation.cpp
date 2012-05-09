#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>

#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/RungeKutta4.h>
#include <Simulation/Integrators/Implementations/RungeKuttaFehlberg45.h>

#include <Visualization/Renderers/LightRenderer.h>
#include <Visualization/Renderers/CoordinateSystemRenderer.h>
#include <Visualization/Renderers/CameraRenderer.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/Renderers/TweakBarRenderer.h>

#include <Simulation/SimulationBuilder.h>

#include <map>
#include <sstream>

using namespace IBDS;
using namespace std;


void create4BoxesWithSpring(SimulationBuilder & b, const Vector3D & offset){  
  Box* box1 =b.createBox("box1",offset+Vector3D::Zero(),0);
  Box* box2= b.createBox("box2",offset+Vector3D(0,-1,0));
  Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0));
  Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));
  
  b.createSpring("spring1","box1","box2",60.0,1, box1->getPosition(), box2->getPosition());
  b.createSpring("spring2","box2","box3",60.0,1, box2->getPosition(), box3->getPosition());
  b.createSpring("spring3","box3","box4",60.0,1, box3->getPosition(), box4->getPosition());
  
}
void createSimplePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
  b.createBox("pendulum",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBallJoint("ball joint 1","fixed point", "pendulum",offset);//create a joint at the particles location

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
  b.setGravity(9.81);

  create4BoxesWithSpring(b, Vector3D(6,0,0));

  createSimplePendulum(b,Vector3D(8,0,0));
  
  }/**/