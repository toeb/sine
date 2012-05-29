#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>
#include <Simulation/Integrators/Implementations/ExplicitEuler.h>
#include <Simulation/Integrators/Implementations/ImplicitEuler.h>
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
#include <Visualization/Renderers/TweakBar/TweakBarRenderer.h>
#include <Visualization/UserInterface/DelegateAction.h>
#include <Visualization/UserInterface/RealValue.h>
#include <Visualization/Renderers/PlaneRenderer.h>
#include <Visualization/InputHandler.h>
#include <Simulation/SimulationBuilder.h>
#include <Simulation/Textiles/TextileModel.h>
#include <Simulation/DynamicsAlgorithm.h>
#include <Visualization/Renderers/SphereRenderer.h>
#include <Visualization/Renderers/CollisionRenderer.h>
#include <Simulation/Collision/Detection/Acceleration/BoundingSphereTree.h>
#include <Visualization/Renderers/BoundingSphereHierarchyRenderer.h>
#include <map>
#include <sstream>
#include <Visualization/Renderers/PolygonRenderer.h>

using namespace IBDS;
using namespace std;

int integratorIndex=0;
vector<SingleStepIntegrator*> integrators;


void CustomSimulation::buildAlgorithms(){
  
  integrators.push_back(new ExplicitEuler(0.01));
  integrators.push_back(new ImplicitEuler(0.01));
  integrators.push_back(new RungeKutta4(0.01));

  
  addSimulationObject(&dynamicsAlgorithm);

  integrator = integrators.at(0);

  integrator->setSystemFunction(dynamicsAlgorithm);
  
  
  setIntegrator(*integrator);
  
  addSimulationObject(new DelegateAction("toggle collision detection",[this](){
    dynamicsAlgorithm.detectCollisions = ! dynamicsAlgorithm.detectCollisions;
    dynamicsAlgorithm.sphereCollisionDetector.resetCollisions();
  }));

  addSimulationObject(new DelegateAction("toggle multibody",[this](){
    dynamicsAlgorithm.doMultiBody = ! dynamicsAlgorithm.doMultiBody;
  }));




  addSimulationObject(new IntValue("Integrator 0-2 (0=ee, 1=ie,2=rk4)", 
    [this](){
      return integratorIndex;
  },
    [this](int val){
      integratorIndex = val % 3;
      integrator= integrators.at(integratorIndex);
      integrator->setSystemFunction(dynamicsAlgorithm);
      setIntegrator(*integrator);

    }));



  addSimulationObject( new RealValue("Integrator Step Size",
    [this](){return integrator->getStepSize();},
    [this](Real value){integrator->setStepSize(value);}));

  


  
  addSimulationObject(new LightRenderer());
  addSimulationObject(new CoordinateSystemRenderer());// renders coordinate system at world origin
  addSimulationObject(new TweakBarRenderer());
  addSimulationObject(new CameraRenderer());
}

void CustomSimulation::buildModel(){ 
  setName("Custom Simulation");
   
  SimulationBuilder b(*this);  
    
  //addSimulationObject(new ControllableBox());

  Gravity & g = *(b.setGravity(1));
  IValue * r = new RealValue("Gravity Magnitude",
    [&g](){return g.getGravityMagnitude();},
    [&g](Real val){g.setGravityMagnitude(val);});

  addSimulationObject(r);

  
  /*
  b.setOffset(Vector3D(10,0,0));
  
  b.createParticle("p1",Vector3D(-1,0,0),0);
  b.createSphere("s1",Vector3D(-3,-0.3,0),1,1);
  b.createBallJoint("j1","s1","p1",Vector3D(-1,0,0));
  
  b.createParticle("p2",Vector3D(1,0,0),0);
  b.createSphere("s2",Vector3D(3,0,0),1,1);
  b.createBallJoint("j2","s2","p2",Vector3D(1,0,0));

  b.createParticle("p3",Vector3D(2,0,0),0);
  b.createSphere("s3",Vector3D(3,0,0),1,1);
  b.createBallJoint("j3","s3","p3",Vector3D(2,0,0));
  */


  //create three geometries and their bounding octrees
  vector<Geometry*> & geoms = *(new vector<Geometry*>());
  b.setOffset(Vector3D(12,0,0));
  Geometry * geom = b.createSphere("",Vector3D::Zero(),0,3);
  geoms.push_back(geom);
  b.setOffset(Vector3D(6,0,0));
  geom = b.createFixedPlane("",Vector3D::Zero(),Quaternion::zeroRotation(),4,2);
  geoms.push_back(geom);
  b.setOffset(Vector3D(2,0,0));
  geoms.push_back(b.createBox("box13",Vector3D::Zero(),0));

  int depth=5;

  for_each(geoms.begin(), geoms.end(), [this, &geoms,&depth](Geometry * geo){
  
    Octree * octree= new Octree(*geo,depth);
    OctreeRenderer & otr= *(new OctreeRenderer(*octree));
    addSimulationObject(octree);
    addSimulationObject(&otr);
    
  });
  addSimulationObject(new DelegateAction("inc octreelevel",[depth](){
      OctreeRenderer::level = (OctreeRenderer::level+1)%(depth+1);
    }));

}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  
  //*
  Connector * connector = dynamic_cast<Connector*>(simulationObject);
  if(connector){
   addSimulationObject(new ConnectorRenderer(*connector));
    //addRenderer(new ConnectorVelocityRenderer(*connector));
    //addRenderer(new ConnectorForceRenderer(*connector));
  }
  
  Particle * particle = dynamic_cast<Particle*>(simulationObject);
  if(particle){
    addSimulationObject(new ParticleRenderer(*particle));
  }

  Hexahedron * box = dynamic_cast<Hexahedron*>(simulationObject);
  if(box){
    //addSimulationObject(new BoxRenderer(*box));
  }

  DampedSpring * spring = dynamic_cast<DampedSpring*>(simulationObject);

  if(spring){
    addSimulationObject(new SpringRenderer(*spring));
  }//*/

  Sphere * sphere = dynamic_cast<Sphere*>(simulationObject);
  if(sphere){
    //addSimulationObject(new SphereRenderer(*sphere));
  }

  DynamicSphere * dSphere = dynamic_cast<DynamicSphere*>(simulationObject);
  if(dSphere){
    addSimulationObject(new Collidable(*dSphere));
   //     addSimulationObject(new SphereRenderer(*sphere));
  }
  Collidable* collidable = dynamic_cast<Collidable*>(simulationObject);

  if(collidable){
    addSimulationObject(new CollisionRenderer(*collidable));
  }

}