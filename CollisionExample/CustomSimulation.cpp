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
#include <Visualization/Renderers/BoundingSphereHierarchyRenderer.h>
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
  CameraRenderer * cam = new CameraRenderer();
  cam->setPosition(Vector3D(8,0,30));
  Quaternion q;
  q.setFromAxisAngle(Vector3D(0,1,0),3.14190/2);
  cam->setOrientation(q);
  addSimulationObject(cam);


}

void CustomSimulation::buildModel(){ 
  setName("Custom Simulation");
   
  SimulationBuilder b(*this);  
    
  //addSimulationObject(new ControllableBox());

  Gravity & g = *(b.setGravity(Vector3D(0,-1,0)));

  
  

  g.setGravityMagnitude(1);
  IValue * r = new RealValue("Gravity Magnitude",
    [&g](){return g.getGravityMagnitude();},
    [&g](Real val){g.setGravityMagnitude(val);});

  addSimulationObject(r);



  
  Sphere * sphere = 0;
  Collidable * collidable;


  b.setOffset(Vector3D(10,3,4));
  Real radius = 0.5;
  b.createParticle("p1",Vector3D(-1,0,0),0);
  sphere = b.createSphere("s1",Vector3D(-3,-0.3,0),1,radius);
  b.createBallJoint("j1","s1","p1",Vector3D(-1,0,0));
  addSimulationObject(new SphereRenderer(*sphere));
  collidable = new Collidable(*sphere);
  addSimulationObject(collidable);
  
  b.createParticle("p2",Vector3D(1,0,0),0);
  sphere= b.createSphere("s2",Vector3D(3,0,0),1,radius);
  b.createBallJoint("j2","s2","p2",Vector3D(1,0,0));
  addSimulationObject(new SphereRenderer(*sphere));
  collidable = new Collidable(*sphere);
  addSimulationObject(collidable);

  b.createParticle("p3",Vector3D(2,0,0),0);
  sphere= b.createSphere("s3",Vector3D(3,0,0),1,radius);
  b.createBallJoint("j3","s3","p3",Vector3D(2,0,0));
  addSimulationObject(new SphereRenderer(*sphere));
  collidable = new Collidable(*sphere);
  addSimulationObject(collidable);
  

  


  //create geometries which are approximated by a bounding tree and add them to the geoms vector
  Geometry * geometry;
  vector<Geometry*> & geoms = *(new vector<Geometry*>());
    
  //sphere
  b.setOffset(Vector3D(18,0,0));
  geometry = b.createSphere("",Vector3D::Zero(),0,2);
  //geoms.push_back(geometry);
  // use Sphere Renderer  
  addSimulationObject(new SphereRenderer(*(dynamic_cast<Sphere*>(geometry))));
  
  
  //rectangle (flat)
  b.setOffset(Vector3D(8,0,0));
  geometry = b.createFixedRectangle("",Vector3D::Zero(),Quaternion::zeroRotation(),4,2);
  geoms.push_back(geometry);
  //use polygon renderer
  addSimulationObject(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  //add position to tweakbar
  addSimulationObject(new Vector3DValue("rectangle",geometry->position()));

  
  //box
  b.setOffset(Vector3D(-5,0,0));
  geometry =  b.createBox("box",Vector3D::Zero(),0); 
  geoms.push_back(geometry);
  //polygon renderer
  addSimulationObject(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  //add position to tweakbar  
  addSimulationObject(new Vector3DValue("box",geometry->position()));


  //triangle
  geometry = new Triangle();  
  geometry->setPosition(Vector3D(-2,0,0));
  addSimulationObject(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  geoms.push_back(geometry);
  addSimulationObject(new Vector3DValue("triangle",geometry->position()));


  //pyramid
  geometry = new Pyramid();
  geometry->setPosition(Vector3D(3,0,0));
 // geometry->setOrientation();
  //position to tweakbar
  addSimulationObject(new Vector3DValue("pyramid", geometry->position()));
  //polygon renderer
  addSimulationObject(new PolygonRenderer(*(dynamic_cast<Polygon*>(geometry))));
  geoms.push_back(geometry);

  //plane
  geometry = new Plane();
  geometry->setPosition(Vector3D(0,-6,0));  
  addSimulationObject(new Vector3DValue("pyramid", geometry->position()));
  addSimulationObject(new PlaneRenderer(*dynamic_cast<Plane*>(geometry)));
  //create a collidable to wrap the plane
  Collidable * planeCollidable = new Collidable(*dynamic_cast<Plane*>(geometry));
  addSimulationObject(planeCollidable);



  //generate octrees
  int depth=5;
 
  for_each(geoms.begin(), geoms.end(), [this, &geoms,&depth](Geometry * geo){
  
    Octree * octree= new Octree(*geo,depth, *(new BoundingSphereFactory()));
    OctreeRenderer & otr= *(new OctreeRenderer(*octree));
    addSimulationObject(octree);
    addSimulationObject(&otr);
    
  });
  
  addSimulationObject(new DelegateAction("inc octreelevel",[depth](){
    OctreeRenderer::level = (OctreeRenderer::level+1)%(depth+1);
      
  }));  
  addSimulationObject(new DelegateAction("renderOctree",[depth](){
    OctreeRenderer::doRender = !OctreeRenderer::doRender;
  }));


   addSimulationObject(new CollisionRenderer(dynamicsAlgorithm.collisionDetector));


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



}