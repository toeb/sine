#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>
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

using namespace IBDS;
using namespace std;

int integratorIndex=0;
vector<SingleStepIntegrator*> integrators;



void CustomSimulation::buildAlgorithms(){  
  integrators.push_back(new ExplicitEuler(0.01));
  integrators.push_back(new ImplicitEuler(0.01));
  integrators.push_back(new RungeKutta4(0.01));

  
  add(&dynamicsAlgorithm);

  integrator = integrators.at(0);

  integrator->setSystemFunction(dynamicsAlgorithm);
  
  
  setIntegrator(*integrator);
  
  add(new DelegateAction("toggle collision detection",[this](){
    dynamicsAlgorithm.detectCollisions = ! dynamicsAlgorithm.detectCollisions;
    dynamicsAlgorithm.collisionDetector.resetCollisions();
  }));

  add(new DelegateAction("toggle multibody",[this](){
    dynamicsAlgorithm.doMultiBody = ! dynamicsAlgorithm.doMultiBody;
  }));



  add(new IntValue("Integrator 0-2 (0=ee, 1=ie,2=rk4)", 
    [this](){
      return integratorIndex;
  },
    [this](int val){
      integratorIndex = val % 3;
      integrator= integrators.at(integratorIndex);
      integrator->setSystemFunction(dynamicsAlgorithm);
      setIntegrator(*integrator);

    }));



  add( new RealValue("Integrator Step Size",
    [this](){return integrator->getStepSize();},
    [this](Real value){integrator->setStepSize(value);}));

  


  
  add(new LightRenderer());
  add(new CoordinateSystemRenderer());// renders coordinate system at world origin
  CameraRenderer * cam = new CameraRenderer();
  cam->position() =Vector3D(8,0,30);
  Quaternion q;
  q.setFromAxisAngle(Vector3D(0,1,0),3.14190/2);
  cam->orientation()  = q;
  add(static_cast<IRenderer*>(cam));


}

void CustomSimulation::buildModel(){ 
  setName("Custom Simulation");
   
  SimulationBuilder b(*this);  
    
  //add(new ControllableBox());

  Gravity & g = *(b.setGravity(Vector3D(0,-1,0)));

  //add collision renderer first so that transparent objects render correctly
  add(new CollisionRenderer(dynamicsAlgorithm.collisionDetector));
  

  add(new IntValue("Number of Collision",[this](){return dynamicsAlgorithm.collisionDetector.getCollisionCount();},[](int val){}));
  add(new IntValue("Number of Contacts",[this](){return dynamicsAlgorithm.collisionDetector.getContactCount();},[](int val){}));

  

  g.setGravityMagnitude(1);
  IValue * r = new RealValue("Gravity Magnitude",
    [&g](){return g.getGravityMagnitude();},
    [&g](Real val){g.setGravityMagnitude(val);});

  add(r);



  //create 3 sphere pendulums that collide
  DynamicSphere * sphere = 0;
  Collidable * collidable;


  b.setOffset(Vector3D(10,3,4));
  Real radius = 0.5;
  b.createParticle("p1",Vector3D(-1,0,0),0);
  sphere = b.createSphere("s1",Vector3D(-3,-0.3,0),1,radius);
  b.createBallJoint("j1","s1","p1",Vector3D(-1,0,0));
  add(new SphereRenderer(sphere->geometry()));
  collidable = new Collidable(sphere->geometry());
  add(collidable);
  
  b.createParticle("p2",Vector3D(1,0,0),0);
  sphere= b.createSphere("s2",Vector3D(3,0,0),1,radius);
  b.createBallJoint("j2","s2","p2",Vector3D(1,0,0));
  add(new SphereRenderer(sphere->geometry()));
  collidable = new Collidable(sphere->geometry());
  add(collidable);

  b.createParticle("p3",Vector3D(2,0,0),0);
  sphere= b.createSphere("s3",Vector3D(3,0,0),1,radius);
  b.createBallJoint("j3","s3","p3",Vector3D(2,0,0));
  add(new SphereRenderer(sphere->geometry()));
  collidable = new Collidable(sphere->geometry());
  add(collidable);
  

  //create a spring pendulum that collides a sphere with the plane at y = 0;


  //create geometries which are approximated by a bounding tree and add them to the geoms vector

  Geometry * geometry;
  vector<Geometry*> & geoms = *(new vector<Geometry*>());
    

  
  
  //rectangle (flat)
  b.setOffset(Vector3D(8,0,0));
  geometry = b.createFixedRectangle("",Vector3D::Zero(),Quaternion::zeroRotation(),4,2);
  geoms.push_back(geometry);
  //use polygon renderer
  add(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  //add position to tweakbar
  add(new Vector3DValue("rectangle",geometry->coordinates().position()));

  
  //box
  b.setOffset(Vector3D(-5,0,0));
  DynamicBox * box =  b.createBox("box",Vector3D::Zero(),0); 
  geoms.push_back(&box->geometry());
  //polygon renderer
  add(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  //add position to tweakbar  
  add(new Vector3DValue("box",geometry->coordinates().position()));


  //triangle
  geometry = new Triangle();  
  geometry->coordinates().position() = Vector3D(-2,0,0);
  add(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  geoms.push_back(geometry);
  add(new Vector3DValue("triangle",geometry->coordinates().position()));


  //pyramid
  geometry = new Pyramid();
  geometry->coordinates().position() = Vector3D(3,0,0);
 // geometry->setOrientation();
  //position to tweakbar
  add(new Vector3DValue("pyramid", geometry->coordinates().position()));
  //polygon renderer
  add(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  geoms.push_back(geometry);

  //plane
  geometry = new Plane();
  geometry->coordinates().position() = Vector3D(0,-6,0);  
  add(new Vector3DValue("pyramid", geometry->coordinates().position()));
  add(new PlaneRenderer(*dynamic_cast<Plane*>(geometry)));
  //create a collidable to wrap the plane
  Collidable * planeCollidable = new Collidable(*dynamic_cast<Plane*>(geometry));
  add(planeCollidable);
  Quaternion & quat = geometry->coordinates().orientation();
  Real & angle = *(new Real());
  add(new RealValue("plane z angle",[&angle](){
    return angle;
  },
    [&angle, &quat](Real value){
      angle = value;
      quat.setFromAxisAngle(Vector3D::e3(),angle);
  }));
  add(new Vector3DValue("plane position", geometry->coordinates().position()));

  //sphere
  b.setOffset(Vector3D(18,0,0));
  DynamicSphere * dynSphere  = b.createSphere("",Vector3D::Zero(),0,2);
  geoms.push_back(&dynSphere->geometry());
  // use Sphere Renderer  
  //add(new SphereRenderer(*(dynamic_cast<Sphere*>(geometry))));

  //generate octrees
  int depth=5;
 
  for_each(geoms.begin(), geoms.end(), [this, &geoms,&depth](Geometry * geo){
  
    Octree * octree= new Octree(*geo,depth, *(new BoundingSphereFactory()));
    OctreeRenderer & otr= *(new OctreeRenderer(*octree));
    add(octree);
    add(&otr);
    
  });
  
  add(new DelegateAction("inc octreelevel",[depth](){
    OctreeRenderer::level = (OctreeRenderer::level+1)%(depth+1);
      
  }));  
  add(new DelegateAction("renderOctree",[depth](){
    OctreeRenderer::doRender = !OctreeRenderer::doRender;
  }));

  //add tweakbar renderer last so it is drawn over everything else  

}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  
  //*
  Connector * connector = dynamic_cast<Connector*>(simulationObject);
  if(connector){
   //add(new ConnectorRenderer(*connector));
    //addRenderer(new ConnectorVelocityRenderer(*connector));
    //addRenderer(new ConnectorForceRenderer(*connector));
  }
  
  Particle * particle = dynamic_cast<Particle*>(simulationObject);
  if(particle){
    add(new ParticleRenderer(*particle));
  }

  Hexahedron * box = dynamic_cast<Hexahedron*>(simulationObject);
  if(box){
    //add(new BoxRenderer(*box));
  }

  DampedSpring * spring = dynamic_cast<DampedSpring*>(simulationObject);

  if(spring){
    add(new SpringRenderer(*spring));
  }//*/

  Sphere * sphere = dynamic_cast<Sphere*>(simulationObject);
  if(sphere){
    //add(new SphereRenderer(*sphere));
  }
}