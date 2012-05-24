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

#include <Visualization/InputHandler.h>

#include <Simulation/SimulationBuilder.h>

#include <Simulation/Textiles/TextileModel.h>

#include <Simulation/DynamicsAlgorithm.h>


#include <map>
#include <sstream>

using namespace IBDS;
using namespace std;

void create4BoxesWithSpring(SimulationBuilder & b, const Vector3D & offset){  
  Box* box1 =b.createBox("box1",offset+Vector3D::Zero(),0);
  Box* box2= b.createBox("box2",offset+Vector3D(0.1,-2,0));
  //Box* box3 = b.createBox("box3",offset+Vector3D(0,-2,0));
  //Box* box4 = b.createBox("box4",offset+Vector3D(0,-3,0));

  //box2->addExternalForce(offset+Vector3D(0,0,0),Vector3D(1,0,0));
  b.createSpring("spring1","box1","box2",60,9, box1->getPosition()-Vector3D(0,0.5,0), box2->getPosition()+Vector3D(0,0.5,0),1.5);
  //b.createSpring("spring2","box2","box3",0.1,0, box2->getPosition(), box3->getPosition());
  //b.createSpring("spring3","box3","box4",0.11,0, box3->getPosition(), box4->getPosition());
  
}

TextileModel *  createCloth(Simulation & s, Real massPerSqrMeter=2.0, Real width = 5, Real height = 5, int rows=30, int cols=30){

  Quaternion q;
  q.setFromAxisAngle(Vector3D(1,0,0),3.14/2);
  Matrix3x3 ori;
  q.getMatrix3x3(ori);

  

  TextileModel * m = TextileModel::createTextileModel(Vector3D(10,0,0),
    ori,massPerSqrMeter*width*height,width,height,rows,cols);
  
  
  m->getNode(0,cols-1)->particle->setMass(0);
  m->getNode(rows-1,cols-1)->particle->setMass(0);
  
 // m->getNode((rows+1)/2,cols-1)->particle->setMass(0);
 
  for_each(m->getSimulationObjects().begin(), m->getSimulationObjects().end(), [&s](ISimulationObject * obj){
    s.addSimulationObject(obj);
  });

  m->setElongationSpringConstant(50);
  m->setFlexionSpringConstant(50);
  m->setShearSpringConstant(50);

  s.addSimulationObject(m);
  // tweak bar entries
  TextileModel & cloth=*m;

  s.addSimulationObject(new DelegateAction("Toggle Cloth Normalization", [&cloth](){
    cloth.setNormalizing(!cloth.isNormalizing());
  }));
  s.addSimulationObject( new RealValue("Maximum Cloth Spring Elongation",
    [&cloth](){return cloth.getMaximumElongation();},
    [&cloth](Real value){cloth.setMaximumElongation(value);}));

  
  s.addSimulationObject( new RealValue("Cloth mass",
    [&cloth](){return cloth.getMass();},
    [&cloth](Real value){cloth.setMass(value);}));


  s.addSimulationObject( new RealValue("Flex Stiffness Constant",
    [&cloth](){return cloth.getFlexionSpringConstant();},
    [&cloth](Real value){cloth.setFlexionSpringConstant(value);}));

  s.addSimulationObject( new RealValue("Flex Dampening Constant",
    [&cloth](){return cloth.getFlexionDampeningConstant();},
    [&cloth](Real value){cloth.setFlexionDampeningConstant(value);}));

  s.addSimulationObject( new RealValue("Elongator Stiffness Constant",
    [&cloth](){return cloth.getElongationSpringConstant();},
    [&cloth](Real value){cloth.setElongationSpringConstant(value);}));

  s.addSimulationObject( new RealValue("Elongator Dampening Constant",
    [&cloth](){return cloth.getElongationDampeningConstant();},
    [&cloth](Real value){cloth.setElongationDampeningConstant(value);}));


  s.addSimulationObject( new RealValue("Shearer Stiffness Constant",
    [&cloth](){return cloth.getShearSpringConstant();},
    [&cloth](Real value){cloth.setShearSpringConstant(value);}));

  s.addSimulationObject( new RealValue("Shearer Dampening Constant",
    [&cloth](){return cloth.getShearDampeningConstant();},
    [&cloth](Real value){cloth.setShearDampeningConstant(value);}));


  return m;



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
  if(s<0.1)s = 0.1;
  Real mass = 1.0 ;
  Real l=0.75;
  Box * lastBox=0;
  Box* currentBox=0;
  Vector3D direction(1,0,0);
  direction.normalize();
  for(int i=0; i < n; i++){
    lastBox = currentBox;
    currentBox = b.createBox("",Vector3D::Zero(),mass,s,s,s);
    currentBox->setPosition((offset+s*(l*i)*direction));
    if(i==0){
      currentBox->setMass(0);
      continue;
    }
    b.createBallJoint("",*(lastBox->getName()),*(currentBox->getName()),(offset+s*(l*i-l/2)*direction));
    //if(i==n-1)currentBox->setMass(1); 
  }
}


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

  //createDoublePendulum(b,Vector3D::Zero());

  //addSimulationObject(new TextRenderer(*(new string("4 Boxes connected by springs")),*(new  Vector3D(4,1,0))));

  TextileModel & cloth = *(createCloth(*this,5,10,10,31,31));
  
  //create4BoxesWithSpring(b, Vector3D(3,0,0));

//  createSimplePendulum(b,Vector3D(8,0,0));

  //createNPendulum(b,Vector3D(13,0,0), 10);
}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
  
  //*
  Connector * connector = dynamic_cast<Connector*>(simulationObject);
  if(connector){
    //addSimulationObject(new ConnectorRenderer(*connector));
    //addRenderer(new ConnectorVelocityRenderer(*connector));
    //addRenderer(new ConnectorForceRenderer(*connector));
  }
  
  Particle * particle = dynamic_cast<Particle*>(simulationObject);
  if(particle){
    //addSimulationObject(new ParticleRenderer(*particle));
  }

  Box * box = dynamic_cast<Box*>(simulationObject);
  if(box){
    addSimulationObject(new BoxRenderer(*box));
  }

  DampedSpring * spring = dynamic_cast<DampedSpring*>(simulationObject);

  if(spring){
    addSimulationObject(new SpringRenderer(*spring));
  }//*/

  

}