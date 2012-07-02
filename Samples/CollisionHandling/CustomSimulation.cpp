#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>
#include <Simulation/Dynamics/Connection/ConnectorFactory.h>
#include <Simulation/Integration/Implementations/ExplicitEuler.h>
#include <Simulation/Integration/Implementations/ImplicitEuler.h>
#include <Simulation/Integration/Implementations/RungeKutta4.h>
#include <Simulation/Integration/Implementations/RungeKuttaFehlberg45.h>
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
#include <Visualization/Renderers/OctreeRenderer.h>
#include <Simulation/Geometry/Plane.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>
#include <map>
#include <sstream>
#include <Visualization/Renderers/PolygonRenderer.h>
#include <Visualization/UserInterface/Vector3DValue.h>
#include <Simulation/Geometry/Mesh/Ply/PlyMesh.h>
using namespace IBDS;
using namespace std;

int integratorIndex=0;
vector<SingleStepIntegrator*> integrators;



void CustomSimulation::buildModel(){ 
  setName("Collision Handling Example");
  
  CollisionRenderer *  collisionRenderer =new CollisionRenderer(dynamicsAlgorithm.collisionDetector);
  addSimulationObject(collisionRenderer);
  SimulationBuilder b(*this);  
  Gravity & g = *(b.setGravity(Vector3D(0,-1,0)));
  g.setGravityMagnitude(0.1);
  
  addSimulationObject(new RealValue("Collisiontrace Timeout",collisionRenderer->timeout()));
  addSimulationObject(new DelegateAction("Collisiontrace", [collisionRenderer](){
    collisionRenderer->renderCollisionTrace() = !collisionRenderer->renderCollisionTrace();

  }));

  g.setGravityMagnitude(0.1);
  addSimulationObject( new RealValue("Gravity Magnitude",
    [&g](){return g.getGravityMagnitude();},
    [&g](Real val){g.setGravityMagnitude(val);}));

  {
    auto plane = new DynamicGeometry<Plane>(*new Plane(),0,Matrix3x3::Identity());
    plane->coordinates().position() = Vector3D(0,-4,0);
    plane->coordinates().orientation().setFromAxisAngle(Vector3D(0,0,1),-0.2);
    addSimulationObject(new Vector3DValue("plane ",plane->coordinates().position()));
    
    addSimulationObject(plane);
    auto renderer = new PlaneRenderer(plane->geometry());
    addSimulationObject(renderer);
    addSimulationObject(new RealValue("plane extent",renderer->extent()));
    addSimulationObject(DynamicCollidable::create(plane->geometry(),plane->body()));
  }

  {
    auto sphere = new DynamicSphere(1,1);
    addSimulationObject(sphere);
    addSimulationObject(new Vector3DValue("sphere",sphere->coordinates().position()));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    sphere->coordinates().position() = Vector3D(1,-2,0);
    addSimulationObject(DynamicCollidable::create(sphere->geometry(),sphere->body(),0.1,100,50));
  }

  {
    auto box = new DynamicBox();
    addSimulationObject(box);
    addSimulationObject(new Vector3DValue("box", box->coordinates().position()));
    addSimulationObject(new BoxRenderer(box->geometry()));
    box->coordinates().position().set(3,2,0);
    addSimulationObject(DynamicCollidable::create(*new Octree(box->geometry(),5,* new BoundingSphereFactory()),box->body(),0.3,100,50));
  }

  {
    auto pyramid = new DynamicGeometry<Pyramid>(*new Pyramid(),1,Matrix3x3::Identity());
    addSimulationObject(pyramid);
    addSimulationObject(new Vector3DValue("pyramid",pyramid->coordinates().position()));
    addSimulationObject(new PolygonRenderer(pyramid->geometry()));
    pyramid->coordinates().position().set(3,1,0);
    addSimulationObject(DynamicCollidable::create(*new Octree(pyramid->geometry(),5,* new BoundingSphereFactory()),pyramid->body(),0.3));
  }

  {
    DynamicSphere * sphere = 0;
    DynamicCollidable * collidable;


    b.setOffset(Vector3D(10,3,4));
    Real radius = 0.5;

    b.createParticle("p6",Vector3D(-2,-1,0),1);
    sphere = b.createSphere("s6",Vector3D(-2,-1,0),1,radius);
    b.createBallJoint("j6","s6","p6",Vector3D(-2,-1,0));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
    addSimulationObject(collidable); 
  
    b.createParticle("p5",Vector3D(-2,0,0),0);
    sphere = b.createSphere("s5",Vector3D(-2,-2,0),2,radius);
    b.createBallJoint("j5","s5","p5",Vector3D(-2,0,0));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
    addSimulationObject(collidable);

    b.createParticle("p4",Vector3D(-1,0,0),0);
    sphere = b.createSphere("s4",Vector3D(-1,-2,0),2,radius);
    b.createBallJoint("j4","s4","p4",Vector3D(-1,0,0));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
    addSimulationObject(collidable);

    b.createParticle("p1",Vector3D(0,0,0),0);
    //sphere = b.createSphere("s1",Vector3D(-3,-0.3,0),1,radius);
    sphere = b.createSphere("s1",Vector3D(0,-2,0),2,radius);
    b.createBallJoint("j1","s1","p1",Vector3D(0,0,0));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
    addSimulationObject(collidable);
  
    b.createParticle("p2",Vector3D(1,0,0),0);
    sphere= b.createSphere("s2",Vector3D(3,0,0),1,radius);
    b.createBallJoint("j2","s2","p2",Vector3D(1,0,0));
    addSimulationObject(new SphereRenderer(sphere->geometry()));
    collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
    addSimulationObject(collidable);
  }
  {
    for(int i= 0; i < 2; i++){
      Particle * p = new Particle();
      
      Sphere * sphere = new Sphere(0.1);
      p->position << sphere->coordinates().position;
      
      Vector3D randVector((rand()%1000)/1000.0,(rand()%1000)/1000.0,(rand()%1000)/1000.0);
      p->position() = randVector*5+Vector3D(7,0,0);
      p->velocity() = randVector*5 - Vector3D(2.5,2.5,2.5);
      

      DynamicCollidable * collidable = DynamicCollidable::create(*sphere,*p);

      addSimulationObject(p);
      addSimulationObject(sphere);
      addSimulationObject(collidable);
      addSimulationObject(new SphereRenderer(*sphere));
    }
  }
}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  
}


  

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
    dynamicsAlgorithm.collisionDetector.resetCollisions();
  }));

  addSimulationObject(new DelegateAction("toggle multibody",[this](){
    dynamicsAlgorithm.doMultiBody = ! dynamicsAlgorithm.doMultiBody;
  }));

  addSimulationObject(new RealValue("time", [this](){return getTime();}, [](Real r){}));

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


  auto cam = new CameraRenderer();
  cam->position() =Vector3D(8,0,30);
  cam->orientation().setFromAxisAngle(Vector3D(0,1,0),PI/2);
  addSimulationObject(cam);

  addSimulationObject(new Vector3DValue("camera position", cam->position()));


}

