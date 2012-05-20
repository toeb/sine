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
#include <Visualization/Renderers/TweakBarRenderer.h>

#include <Visualization/InputHandler.h>

#include <Simulation/SimulationBuilder.h>

#include <Simulation/Textiles/TextileModel.h>

#include <Simulation/DynamicsAlgorithm.h>


#include <map>
#include <sstream>

using namespace IBDS;
using namespace std;





class ControllableBox : public  Box,  public IInputListener,  public Force{
public:
  bool l,r,u,d;
  ControllableBox():Box(1,1,1,1){
    l=r=u=d=false;
  }
   void onKeyDown(Keys key){
     switch(key){
      case Keys::KEY_W: u = true; break;
      case Keys::KEY_A: l = true; break;
      case Keys::KEY_S: d = true; break;
      case Keys::KEY_D: r = true; break;
     }
  }
   void onKeyUp(Keys key){
     switch(key){
      case Keys::KEY_W: u = false; break;
      case Keys::KEY_A: l = false; break;
      case Keys::KEY_S: d = false; break;
      case Keys::KEY_D: r = false; break;
     }
  }
  void act( std::vector<DynamicBody*> & target, Real time){
   // addExternalForce(Vector3D(0,9.81,0));
    if(u) addExternalForce(Vector3D(0,1,0));
    if(d) addExternalForce(Vector3D(0,-1,0));
    if(l) addExternalForce(Vector3D(-1,0,0));
    if(r) addExternalForce(Vector3D(1,0,0));
  }

};

void create4BoxesWithSpring(SimulationBuilder & b, const Vector3D & offset){  
  Box* box1 =b.createBox("box1",offset+Vector3D::Zero(),0);
  Box* box2= b.createBox("box2",offset+Vector3D(0,-1,0));
  Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0));
  Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));

  //box2->addExternalForce(offset+Vector3D(0,0,0),Vector3D(1,0,0));
  b.createSpring("spring1","box1","box2",0.5,0, box1->getPosition(), box2->getPosition());
  b.createSpring("spring2","box2","box3",0.1,0, box2->getPosition(), box3->getPosition());
  b.createSpring("spring3","box3","box4",0.11,0, box3->getPosition(), box4->getPosition());
  
}

void createCloth(Simulation & s){
  int rows = 20;
  int cols = 20;
  TextileModel * m = TextileModel::createTextileModel(Vector3D(10,0,0),
    Matrix3x3::Identity(),5,5,rows,cols);
  
  
  m->getNode(0,cols-1)->particle->setMass(0);
  m->getNode(rows-1,cols-1)->particle->setMass(0);
 
  for_each(m->_simulationObjects.begin(), m->_simulationObjects.end(), [&s](ISimulationObject * obj){
    s.addSimulationObject(obj);
  });

  s.addSimulationObject(m);

}
void createSimplePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("fixed point",offset,0);// fixed particle
  b.createBox("pendulum",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBallJoint("ball joint 1","fixed point", "pendulum",offset);//create a joint at the particles location

}
void createDoublePendulum(SimulationBuilder & b, const Vector3D & offset){
  Real l =4;
  b.createParticle("double pendulum fixed point",offset,0);// fixed particle
 
  b.createBox("leg1",offset+Vector3D(l/2+0.1,0,0),1,l,0.2,0.2);//pendulum in x direction (with a small offset so a space is shown between the particle and the bar)
  b.createBox("leg2",offset+Vector3D(l+l/2+0.2,0,0),1,l,0.2,0.2);
  b.createBallJoint("ball joint 12","double pendulum fixed point", "leg1",offset);//create a joint at the particles location
  b.createBallJoint("ball joint 22","leg1", "leg2",Vector3D(l+0.1,0,0));//create a joint at the particles location

}

void createNPendulum(SimulationBuilder & b, const Vector3D & offset, int n){
  Real s = 10.0/n;
  Real l=0.75;
  Box * lastBox=0;
  Box* currentBox=0;
  Vector3D direction(1,1,0);
  direction.normalize();
  for(int i=0; i < n; i++){
    lastBox = currentBox;
    currentBox = b.createBox("",Vector3D::Zero(),1,s,s,s);
    currentBox->setPosition(s*(offset+(l*i)*direction));
    if(i==0){
      currentBox->setMass(0);
      continue;
    }
    b.createBallJoint("",*(lastBox->getName()),*(currentBox->getName()),s*(offset+(l*i-l/2)*direction));
    if(i==n-1)currentBox->setMass(1); 
  }
}

void CustomSimulation::buildAlgorithms(){
  integrator = new RungeKutta4(0.01);
  //integrator = new ExplicitEuler();

  addSimulationObject(&dynamicsAlgorithm);

  integrator->setSystemFunction(dynamicsAlgorithm);
  setIntegrator(*integrator);
  
  addSimulationObject(new LightRenderer());
  addSimulationObject(new CoordinateSystemRenderer());// renders coordinate system at world origin
  addSimulationObject(new CameraRenderer());
  addSimulationObject(new TweakBarRenderer());
}

void CustomSimulation::buildModel(){ 
  setName("Custom Simulation");

  
 
  SimulationBuilder b(*this);  

  
  //addSimulationObject(new ControllableBox());

  b.setGravity(0.1);

  //createDoublePendulum(b,Vector3D::Zero());

  //addSimulationObject(new TextRenderer(*(new string("4 Boxes connected by springs")),*(new  Vector3D(4,1,0))));

  createCloth(*this);

  //create4BoxesWithSpring(b, Vector3D(6,0,0));

  //createSimplePendulum(b,Vector3D(8,0,0));

  //createNPendulum(b,Vector3D(13,0,0), 100);

  
}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  

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

  Box * box = dynamic_cast<Box*>(simulationObject);
  if(box){
    addSimulationObject(new BoxRenderer(*box));
  }

  DampedSpring * spring = dynamic_cast<DampedSpring*>(simulationObject);

  if(spring){
    addSimulationObject(new SpringRenderer(*spring));
  }

  

}